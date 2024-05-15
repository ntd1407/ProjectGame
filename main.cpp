#include "CommonFunc.h"
#include "BaseObject.h"
#include "Player.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"

BaseObject g_pre_menu;
BaseObject g_background;
BaseObject g_instruction;
BaseObject g_highscore;
TTF_Font* font_time = NULL;
TTF_Font* font_highscore = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "-1");

    g_window = SDL_CreateWindow("HELI",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    if(TTF_Init() == - 1)
    {
        success = false;
    }
    font_time  = TTF_OpenFont("Images\\_con.ttf",50);
    if(font_time == NULL)
    {
        success = false;
    }
    font_highscore = TTF_OpenFont("Images\\_con.ttf",75);
    if(font_highscore == NULL)
    {
        success = false;
    }
    return success;
}
bool LoadBackground()
{
    bool ret = g_background.LoadImg("Images\\background.bmp", g_screen);
    return ret;
}


void close()
{
    g_background.Free();
    g_pre_menu.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}
int menumenu(){
	menu = SDL_LoadBMP("Images\\menu.bmp");
	if(menu == NULL){
		printf("Error Creating Menu\n");
		SDL_DestroyRenderer(g_screen);
		SDL_DestroyWindow(g_window);
		SDL_Quit();
		return 1;
	}

	menu_tex = SDL_CreateTextureFromSurface(g_screen,menu);
	SDL_FreeSurface(menu);
	if(menu_tex == NULL){
		printf("Error Creating Menu Texture: %s\n",SDL_GetError());
		SDL_DestroyRenderer(g_screen);
		SDL_DestroyWindow(g_window);
		SDL_Quit();
		return 1;
	}
	SDL_RenderCopy(g_screen,menu_tex,NULL,NULL);

	{
		font  = TTF_OpenFont("Images\\_con.ttf",1000);
		if(font == NULL) std::cout << "Error font";
		SDL_Texture *text[4];
		SDL_Color text_color = {255,255,255,255};
		SDL_FreeSurface(menu_surface);
		menu_surface = TTF_RenderText_Solid(font,"NEW GAME",text_color);
		text[0] = SDL_CreateTextureFromSurface(g_screen,menu_surface);
		SDL_FreeSurface(menu_surface);
		menu_surface = TTF_RenderText_Solid(font,"HIGHSCORE",text_color);
		text[1] = SDL_CreateTextureFromSurface(g_screen,menu_surface);
		SDL_FreeSurface(menu_surface);
		menu_surface = TTF_RenderText_Solid(font,"INSTRUCTIONS",text_color);
		text[2] = SDL_CreateTextureFromSurface(g_screen,menu_surface);
		SDL_FreeSurface(menu_surface);
		menu_surface = TTF_RenderText_Solid(font,"QUIT",text_color);
		text[3] = SDL_CreateTextureFromSurface(g_screen,menu_surface);
		SDL_Rect text_position;
		int i,j;
		for(i=0,j=0;i<4;i++,j+=200){
			text_position.x = 1000;
			text_position.y = -50+j;
			text_position.w = 300;
			text_position.h = 250;
			SDL_RenderCopy(g_screen,text[i],NULL,&text_position);
		}
		SDL_RenderPresent(g_screen);


		SDL_Event e;
		bool menu_run = true;
		while(menu_run){
			if(SDL_PollEvent(&e)){
				switch(e.type){
					case SDL_QUIT :
						menu_run =false;
						break;
					case SDL_MOUSEBUTTONDOWN:
					{
						if(e.motion.x>=1000&&e.motion.x<=1300&&e.motion.y>=-50&&e.motion.y<200){
							return 0;
							break;
						}
						if(e.motion.x>=1000&&e.motion.x<=1300&&e.motion.y>=200&&e.motion.y<400){
							return 1;
							break;
						}
						if(e.motion.x>=1000&&e.motion.x<=1300&&e.motion.y>=400&&e.motion.y<650){
							return 2;
							break;
						}
						if(e.motion.x>=1000&&e.motion.x<=1300&&e.motion.y>=650&&e.motion.y<=900){
							return 3;
							break;
						}
					}
					default:
					break;
				}
			}
		}
	}
}
int highscore(int t) {
    std::ifstream fin("highscore.txt");
    std::vector<int> scores;
    int score;

    while (fin >> score) {
        scores.push_back(score);
    }
    fin.close();

    scores.push_back(t);
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > 3) {
        scores.resize(3);
    }
    std::ofstream fout("highscore.txt");
    for (int i = 0; i < scores.size(); ++i) {
        fout << scores[i] << std::endl;
    }
    fout.close();
    return scores[2];
}

std::vector<ThreatsObject*> MakeThreadList()
{

    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* thread_objs = new ThreatsObject[NUM_THREAT];
    for (int i = 0; i < NUM_THREAT ; i++)
    {
        ThreatsObject* thread_obj = (thread_objs+i);
        if (thread_obj != NULL)
        {
            thread_obj->LoadImg("Images\\object.bmp", g_screen);
            list_threats.push_back(thread_obj);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[])
{
    ImpTimer fbs_timer;
    if (InitData() == false)
    {
        return -1;
    }
    if (!LoadBackground())
    {
        return -1;
    }

        bool start_play = false;
        int time_menu = 0 ;
        int last_time = 0;


	g_pre_menu.LoadImg("Images\\pre_menu.bmp", g_screen);
	g_pre_menu.Render(g_screen,NULL);
	SDL_RenderPresent(g_screen);
	SDL_Delay(500);
    SDL_RenderClear(g_screen);
here:
int menu_menu = menumenu();
std::cout << "menu: " << menu_menu  << std::endl;
        if(!start_play){
            time_menu = SDL_GetTicks()/1000;
        }
    if(menu_menu == 0){

        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1048);
		Mix_Music*backgroundSound = Mix_LoadMUS("audio//Action.mid");
		Mix_PlayMusic(backgroundSound, -1);

        Player p_player;
        BaseObject g_life;
        BaseObject g_gameover;
        g_life.SetLife(3);

        //Time text
        TextObject score;
        score.setColor(TextObject::WHITE_TEXT);
        unsigned int val_score = 0;

        p_player.LoadImg("Images\\player.bmp",g_screen);
        std::vector<ThreatsObject*> threats_list = MakeThreadList();
    bool is_quit = false;
        while (!is_quit)
    {
        fbs_timer.start();
        start_play = true;
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            if(g_event.key.keysym.scancode==SDL_SCANCODE_ESCAPE){
                    Mix_FreeMusic(backgroundSound);
                    Mix_CloseAudio();
                    last_time += val_score + time_menu;
 					goto here;
 				}
            p_player.HandleInputAction(g_event,g_screen);
        }


        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
                                RENDER_DRAW_COLOR,
                                RENDER_DRAW_COLOR,
                                RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen,NULL);

        p_player.HandleBullet(g_screen);
        p_player.DoPlayer();
        p_player.Show(g_screen);


        // hiện threats và xử lí va chạm
    for(int i = 0; i < threats_list.size();i++)
    {

            ThreatsObject* p_threat = threats_list.at(i);
            if(p_threat != NULL)
            {
                p_threat->DoPlayer();
                p_threat->Show(g_screen);
                if(p_threat->CheckToMap()){
                     g_life.SetLife(g_life.Getlife()- 1);
                }
                p_threat->set_check(false);
            }
              bool is_col = SDLCommonFunc::CheckCollision(p_player.GetRect(), p_threat->GetRect());
                   if (is_col)
                   {
                       Mix_Chunk* loseSound = Mix_LoadWAV("audio//two_beep_.wav");
                       Mix_PlayChannel(-1, loseSound, 0);

                       p_player.RemoveBullet(i);
                       p_threat->Reset();
                       g_life.SetLife(g_life.Getlife()- 1);
                   }
            std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();

            for (int am = 0; am < bullet_arr.size(); am++)
            {
                BulletObject* p_bullet = bullet_arr.at(am);
                if (p_bullet)
             {

               for (int i = 0; i < threats_list.size(); i++)
               {
                   ThreatsObject* obj_threat = threats_list.at(i);

                   bool is_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
                   if (is_col)
                   {
                       Mix_Chunk* explosionSound = Mix_LoadWAV("audio//Bomb1.wav");
                       Mix_PlayChannel(-1, explosionSound, 0);
                       p_player.RemoveBullet(am);
                       p_threat->Reset();
                   }
                }
              }
            }


            if(g_life.Getlife() <= 0) {
                highscore(val_score);
                g_gameover.LoadImg("Images//gameover.bmp",g_screen);
                g_gameover.SetRect_w_h(1500,1000);
                g_gameover.Render(g_screen,NULL);
                 std::string str_score = "";
        if(val_score > highscore(val_score))
        {
            str_score += "New highscore: ";
            str_score += std::to_string(val_score);
            score.SetText(str_score);
            score.loadFromRenderedText(font_time, g_screen);
            score.RenderText(g_screen, SCREEN_WIDTH-7*50, 0);
        }
        else{
            str_score += "Your score: ";
            str_score += std::to_string(val_score);
            score.SetText(str_score);
            score.loadFromRenderedText(font_time, g_screen);
            score.RenderText(g_screen, SCREEN_WIDTH - 6*50, 0);
        }
             SDL_RenderPresent(g_screen);
             Mix_FreeMusic(backgroundSound);
             Mix_CloseAudio();
                          SDL_Delay(3000);
                          last_time += val_score + time_menu + 3;
             goto here;
            }
            if(g_life.Getlife() > 0)
            {
                g_life.LoadImg("Images//life.bmp",g_screen);
                g_life.SetRect(100,50);
                g_life.Render(g_screen,NULL);
            }
            if(g_life.Getlife() > 1)
            {
                g_life.LoadImg("Images//life.bmp",g_screen);
                g_life.SetRect(170,50);
                g_life.Render(g_screen,NULL);
            }
            if(g_life.Getlife() > 2)
            {
                g_life.LoadImg("Images//life.bmp",g_screen);
                g_life.SetRect(240,50);
                g_life.Render(g_screen,NULL);
            }

    }
    // show game time
        std:: string str_time = "SCORE: ";
        int time_val = SDL_GetTicks()/1000 - time_menu - last_time;
        if(g_life.Getlife() > 0)
        {
            val_score = time_val;  // để khi game_over dừng cập nhật val_score
        }


        std::string str_val = std::to_string(val_score);
        str_time += str_val;
        score.SetText(str_time);
        score.loadFromRenderedText(font_time, g_screen);
        score.RenderText(g_screen, SCREEN_WIDTH - 200, 0);

        SDL_RenderPresent(g_screen);

        int real_imp_time = fbs_timer.get_ticks();
        int time_one_frame = 1000/FRAMES_PER_SECOND;
        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }
}
else if (menu_menu == 1) {
    g_highscore.LoadImg("Images//highscore.bmp", g_screen);
    std::vector<TextObject> highscores;
    std::ifstream fin("highscore.txt");
    if (!fin.is_open()) {
        std::cout << "Error opening file highscore" << std::endl;
    } else {
        int score;
        int idx = 1;
        while (fin >> score) {
            TextObject text;
            std::string str_highscore = "Top ";
            str_highscore += std::to_string(idx) + " : "+std::to_string(score);
            idx ++;
            text.SetText(str_highscore);
            text.setColor(TextObject:: RED_TEXT);
            if (!text.loadFromRenderedText(font_highscore, g_screen)) {
                std::cout << "Error rendering text" << std::endl;
            } else {
                highscores.push_back(text);
            }
        }
        fin.close();
    }
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
                goto here;
            }
            switch (g_event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        g_highscore.Render(g_screen, NULL);
        for (int i = 0; i < highscores.size(); i++) {
            highscores[i].RenderText(g_screen, SCREEN_WIDTH/2 - 140, SCREEN_HEIGHT/2 - 75*2.5 + i*75);
        }

        SDL_RenderPresent(g_screen);
    }
}


else if(menu_menu == 2){
     g_instruction.LoadImg("Images//instruction.bmp",g_screen);
     bool running = true;
 		while(running){
 			while(SDL_PollEvent(&g_event)){
 				if(g_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                    goto here;
 				}
 				switch(g_event.type){
 					case SDL_QUIT:
 						running = false;
 						break;
 				}
 			}
                g_instruction.Render(g_screen,NULL);
                SDL_RenderPresent(g_screen);
 		}
}
else if(menu_menu == 3){
    close();
    SDL_Quit();
}

    close();
    return 0;
}
