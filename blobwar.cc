#include"blobwar.h"
#include<sstream>
#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

static int eventfilter(const SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_f:
            if (event->key.keysym.mod & KMOD_ALT)
                game->fullscreen();
            return 0;
        default:
            break;
        }
    }

    if (event->type == SDL_QUIT)
    {
        game->quit();
        return 0;
    }

    return 1;
}

#ifdef __APPLE__
static SDL_Surface* core_graphics_image_load(const string& filename)
{
    CFStringRef path = CFStringCreateWithCString(NULL, filename.c_str(), kCFStringEncodingUTF8);
    if (path == NULL) return NULL;

    CFURLRef url = CFURLCreateWithFileSystemPath(NULL, path, kCFURLPOSIXPathStyle, false);
    CFRelease(path);
    if (url == NULL) return NULL;

    CGImageSourceRef source = CGImageSourceCreateWithURL(url, NULL);
    CFRelease(url);
    if (source == NULL) return NULL;

    CGImageRef cgimage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
    CFRelease(source);
    if (cgimage == NULL) return NULL;

    size_t width = CGImageGetWidth(cgimage);
    size_t height = CGImageGetHeight(cgimage);
    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                (int)width,
                                                (int)height,
                                                32,
                                                0x00ff0000,
                                                0x0000ff00,
                                                0x000000ff,
                                                0xff000000);
    if (surface == NULL)
    {
        CGImageRelease(cgimage);
        return NULL;
    }

    bool locked = SDL_MUSTLOCK(surface);
    if (locked && SDL_LockSurface(surface) != 0)
    {
        SDL_FreeSurface(surface);
        CGImageRelease(cgimage);
        return NULL;
    }

    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(surface->pixels,
                                                 width,
                                                 height,
                                                 8,
                                                 surface->pitch,
                                                 colorspace,
                                                 kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    CGColorSpaceRelease(colorspace);
    if (context == NULL)
    {
        if (locked) SDL_UnlockSurface(surface);
        SDL_FreeSurface(surface);
        CGImageRelease(cgimage);
        return NULL;
    }

    CGContextClearRect(context, CGRectMake(0, 0, width, height));
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), cgimage);
    CGContextRelease(context);
    if (locked) SDL_UnlockSurface(surface);
    CGImageRelease(cgimage);

    return surface;
}
#endif

#ifdef WM_ICON
static SDL_Surface* LoadIconSurface(char* file, Uint8** maskp)
{
    SDL_Surface* icon;
    Uint8* pixels;
    Uint8* mask;
    Uint32 mlen, i;

    *maskp = NULL;

    /* Load the icon surface */
    icon = SDL_LoadBMP(file);
    if (icon == NULL)
    {
        cerr << "Couldn't load" << file << " : " << SDL_GetError() << endl;
        return (NULL);
    }

    /* Check width and height */
    if ((icon->w % 8) != 0)
    {
        cerr << "Icon width must be a multiple of 8!" << endl;
        SDL_FreeSurface(icon);
        return (NULL);
    }
    if (icon->format->palette == NULL)
    {
        cerr << "Icon must have a palette!" << endl;
        SDL_FreeSurface(icon);
        return (NULL);
    }

    /* Set the colorkey */
    SDL_SetColorKey(icon, SDL_SRCCOLORKEY, *((Uint8*)icon->pixels));

    /* Create the mask */
    pixels = (Uint8*)icon->pixels;
    mlen = icon->w * icon->h;
    mask = new Uint8[mlen / 8];
    if (mask == NULL)
    {
        cerr << "Out of memory!" << endl;
        SDL_FreeSurface(icon);
        return (NULL);
    }
    memset(mask, 0, mlen / 8);
    for (i = 0; i < mlen;)
    {
        if (pixels[i] != *pixels)
            mask[i / 8] |= 0x01;
        ++i;
        if ((i % 8) != 0)
            mask[i / 8] <<= 1;
    }
    *maskp = mask;
    return (icon);
}
#endif

/** Initialize sound card, and display */
blobwar::blobwar()
{
    pthread_mutex_init(&mutex, NULL);

    SDL_Color clrFg, clrBg;
#ifdef  WM_ICON
    Uint8* iconmask;
#endif
    game = this;
#ifdef DEBUG
    cout << "Initializing SDL" << endl;
#endif
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }

#ifdef DEBUG
    cout << "Opening video" << endl;
#endif
    SDL_WM_SetCaption("Blob War", "Blob War");
#ifdef WM_ICON
    string icon_name = rename("graphx/icon.bmp");
    SDL_Surface* icon = LoadIconSurface((char*)icon_name.c_str(), &iconmask);
    SDL_WM_SetIcon(icon, iconmask);
#endif
    screen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        cout << "Unable to set video mode: " << SDL_GetError() << endl;
        exit(2);
    }

    //initializing font engine and loading fonts
#ifdef DEBUG
    cout << "initializing fonts" << endl;
#endif

    TTF_Init();
    clrFg.r = 255;
    clrFg.g = 255;
    clrFg.b = 255;
    clrFg.unused = 0;
    clrBg.r = 0;
    clrBg.g = 254;
    clrBg.b = 0;
    clrBg.unused = 0;
    bigfont = new font("Vera.ttf", clrFg, clrBg, 18);
    clrFg.r = 0;
    clrFg.g = 0;
    clrFg.b = 240;
    clrFg.unused = 0;
    clrBg.r = 0;
    clrBg.g = 254;
    clrBg.b = 0;
    clrBg.unused = 0;
    smallfont = new font("Vera.ttf", clrFg, clrBg, 10);
    TTF_Quit();

    //init event loop filter
    SDL_SetEventFilter(&eventfilter);

#ifdef SOUND
    //init sound
    sound_engine = new sound();
#endif


#ifdef LIGHT
    framerate = 10;
#else
    framerate = 20;
#endif

    //init mouse
    mousepointer = new mouse();

#ifdef DEBUG
    cout << "Network init" << endl;
#endif
    bwnet = new network();

    //init some widgets
    background = new image("background.png", false);
    background->set_fullscreen();
    background_logo = new image("blobs.png");
    background_logo->set_fullscreen();

    SDL_Rect pos;
    pos.x = 150;
    pos.y = 100;
    pos.w = 200;
    pos.h = 80;
    oneplayergamebutton = new button(pos, "Start 1P game");
    oneplayergamebutton->setcallback(7);
    pos.y += 110;
    twoplayersgamebutton = new button(pos, "Start 2P game");
    twoplayersgamebutton->setcallback(2);
    pos.y += 110;
    networkgamebutton = new button(pos, "Start network game");
    networkgamebutton->setcallback(8);

    pos.x = 450;
    pos.y = 100;
    twoplayerAIbutton = new button(pos, "Start 2P AI");
    twoplayerAIbutton->setcallback(9);
    pos.y += 110;
    twoplayerCOMPbutton = new button(pos, "Start 2P COMP");
    twoplayerCOMPbutton->setcallback(11);
    pos.y += 110;
#ifdef fourplayers
    fourplayerAIbutton = new button(pos, "Start 4P AI");
    fourplayerAIbutton->setcallback(10);
    pos.y += 110;
#endif
    quitbutton = new button(pos, "Quit");
    quitbutton->setcallback(1);

    pos.x = 250;
    pos.w = 300;
    pos.y = 60;
    pos.h = 60;
    boardlabel = new label(pos, "", game->bigfont);
    boardlabel->hide();

    pos.x = 170;
    pos.w = 60;
    pos.y = 60;
    pos.h = 60;
    previousboardbutton = new button("left.png", pos);
    previousboardbutton->hide();
    previousboardbutton->setcallback(3);
    pos.x = 570;
    nextboardbutton = new button("right.png", pos);
    nextboardbutton->hide();
    nextboardbutton->setcallback(4);

    bwboard = new board();
    bwboard->hide();

    pos.x = 300;
    pos.w = 200;
    pos.y = 450;
    pos.h = 80;
    startgamebutton = new button(pos, "Start!");
    startgamebutton->setcallback(5);
    startgamebutton->hide();

    pos.x = 0;
    pos.y = 20;
    pos.w = 800;
    pos.h = 100;

    mainlabel = new label(pos, "", game->bigfont);
    mainlabel->hide();

    pos.x = 0;
    pos.y = 540;
    pos.w = 200;
    pos.h = 60;

    local_player_label = new label(pos, "", game->bigfont);
    local_player_label->hide();

    pos.x = 430;
    pos.w = 370;
    pos.y = 540;
    pos.h = 60;
    scoreslabel = new label(pos, "", game->bigfont);
    scoreslabel->hide();


    winner_images[0] = new image("draw.png", false);
    winner_images[0]->set_fullscreen();
    winner_images[0]->hide();

    winner_images[1] = new image("redwins.png", false);
    winner_images[1]->set_fullscreen();
    winner_images[1]->hide();

    winner_images[2] = new image("bluewins.png", false);
    winner_images[2]->set_fullscreen();
    winner_images[2]->hide();

    winner_images[3] = new image("greenwins.png", false);
    winner_images[3]->set_fullscreen();
    winner_images[3]->hide();

    winner_images[4] = new image("yellowwins.png", false);
    winner_images[4]->set_fullscreen();
    winner_images[4]->hide();

    winner_images[5] = new image("disconnected.png", false);
    winner_images[5]->set_fullscreen();
    winner_images[5]->hide();

    pos.x = 550;
    pos.w = 200;
    pos.y = 240;
    pos.h = 70;
    winlabel1 = new label(pos, "", game->bigfont);
    winlabel1->hide();
    pos.y = 340;
    winlabel2 = new label(pos, "", game->bigfont);
    winlabel2->hide();

    pos.x = 300;
    pos.w = 200;
    pos.y = 450;
    pos.h = 80;
    wingamebutton = new button(pos, "OK");
    wingamebutton->setcallback(6);
    wingamebutton->hide();

    bwrules = NULL;
    frame = 0;

    display2update = 1;
    update();
}

/** shuts down audio and video, and freeing images, music*/
blobwar::~blobwar()
{
#ifdef DEBUG
    cout << "Shutting down game" << endl;
#endif
#ifdef SOUND
    delete sound_engine;
#endif

    //stopping SDL
    SDL_Quit();
    exit(0);
}

/** loads an image
 * \param filename : relative filename */
SDL_Surface* blobwar::image_load(string filename)
{
    string realname = rename("graphx/" + filename);
    SDL_Surface* image = NULL;
#ifdef __APPLE__
    image = core_graphics_image_load(realname);
#endif
    if (image == NULL)
    {
        image = IMG_Load(realname.c_str());
    }
#ifdef DEBUG
    if (image == NULL)
    {
        cerr << "Warning : unable to load : " << realname << " : " <<
            SDL_GetError() << endl;
        return NULL;
    }
#endif

    SDL_Surface* final = SDL_DisplayFormat(image);
    SDL_FreeSurface(image);
    return final;
}

/** loads a transparent image
 * \param filename : relative filename */
SDL_Surface* blobwar::alpha_image_load(string filename)
{
    string realname = rename("graphx/" + filename);
    SDL_Surface* image = NULL;
#ifdef __APPLE__
    image = core_graphics_image_load(realname);
#endif
    if (image == NULL)
    {
        image = IMG_Load(realname.c_str());
    }
#ifdef DEBUG
    if (image == NULL)
    {
        cerr << "Warning : unable to load : " << realname << " : " <<
            SDL_GetError() << endl;
        return NULL;
    }
#endif

    SDL_Surface* final = SDL_DisplayFormatAlpha(image);
    SDL_FreeSurface(image);
    return final;
}

/**converts filename for matching installation path,
 * remember to free strings manually
 * \param shortname: the relative filename*/
string blobwar::rename(string shortname)
{
    return "data/" + shortname;
}


/** updates the screen flip or updaterect */
void blobwar::update()
{
    pthread_mutex_lock(&mutex);
    if (display2update != 0)
    {
        for (list<widget*>::iterator it = widgets.begin(); it != widgets.end(); it++)
            if (!(*it)->is_hidden()) (*it)->display();
        mousepointer->display();
        SDL_Flip(screen);
        display2update = 0;
    }
    pthread_mutex_unlock(&mutex);
}


void blobwar::quit()
{
    cout << "Quitting game" << endl;
    delete game;
}

void blobwar::fullscreen()
{
    if (SDL_WM_ToggleFullScreen(screen))
    {
        cout << "Toggled fullscreen mode - now "
            << ((screen->flags & SDL_FULLSCREEN) ? "fullscreen" : "windowed")
            << endl;
    }
    else
    {
        cout << "Unable to toggle fullscreen mode" << endl;
    }
}

void blobwar::black()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
}

void blobwar::handle()
{
    SDL_Event event;

    //handle network
    bwnet->handle();

    //handle events
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            mousepointer->move(&event);
            break;
        default:
            break;

        case SDL_KEYDOWN:

            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                if (event.key.keysym.mod & KMOD_CTRL)
                    quit();
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            mousepointer->click();
            break;
        }
    }
}

void blobwar::register_widget(widget* w)
{
    widgets.push_back(w);
}

void blobwar::unregister_widget(widget* w)
{
    widgets.remove(w);
}

void blobwar::execute(Uint32 n)
{
    switch (n)
    {
    case 0:
        return;
    case 1:
        //exit game
        quit();
        return;
    case 2:
        //start a two players game (local)
        gametype = GAME2P;
        //gametype = GAME4P;
        board_selection();
        return;
    case 3:
        //display previous map in the list
        if (gametype == NETGAME)
        {
            bwnet->change_map(bwboard->get_previous_board());
        }
        else
        {
            bwboard->previous_board();
        }
        return;
    case 4:
        //display next map in the list
        if (gametype == NETGAME)
        {
            bwnet->change_map(bwboard->get_next_board());
        }
        else
        {
            bwboard->next_board();
        }
        return;
    case 5:
        //start the game
        if (gametype == NETGAME)
        {
            bwnet->send("/start\n");
        }
        else
        {
#define NO_ARG 5
            start_game(NO_ARG);
        }
        return;
    case 6:
        //back to mainmenu
        for (Uint16 i = 0; i < 6; i++)
        {
            winner_images[i]->hide();
        }
        winlabel1->hide();
        winlabel2->hide();
        wingamebutton->hide();
        background_logo->show();
        twoplayersgamebutton->show();
        oneplayergamebutton->show();
        quitbutton->show();
        networkgamebutton->show();
        twoplayerAIbutton->show();
        twoplayerCOMPbutton->show();
#ifdef fourplayers
        fourplayerAIbutton->show();
#endif
        return;
    case 7:
        //start a one player game
        gametype = GAME1P;
        board_selection();
        return;
    case 9:
        // start 2P IA game (local)
        gametype = GAME2PMATCH;
        board_selection();
        return;
    case 11:
        // start 2P IA COMP game (local)
        gametype = GAME2PCOMP;
        board_selection();
        return;
    case 10:
        // start 2P IA game (local)
        gametype = GAME4PMATCH;
        board_selection();
        return;
    case 8:
        //start network game
        char* map = bwnet->connect();
        if (map != NULL)
        {
            //connection successful, go to board selection
            board_selection(map);
            gametype = NETGAME;
        }
        return;
    }
}

void blobwar::board_selection()
{
    //first we hide all buttons
    background_logo->hide();
    twoplayersgamebutton->hide();
    oneplayergamebutton->hide();
    quitbutton->hide();
    networkgamebutton->hide();
    twoplayerAIbutton->hide();
    twoplayerCOMPbutton->hide();
#ifdef fourplayers
    fourplayerAIbutton->hide();
#endif
    //show board
    boardlabel->show();
    previousboardbutton->show();
    nextboardbutton->show();
    startgamebutton->show();
    bwboard->show();

    display2update = 1;
    update();
}

void blobwar::board_selection(char* mapname)
{
    //first we hide all buttons
    background_logo->hide();
    twoplayersgamebutton->hide();
    oneplayergamebutton->hide();
    quitbutton->hide();
    networkgamebutton->hide();
    twoplayerAIbutton->hide();
    twoplayerCOMPbutton->hide();
#ifdef fourplayers
    fourplayerAIbutton->hide();
#endif
    //show board
    boardlabel->show();
    previousboardbutton->show();
    nextboardbutton->show();
    startgamebutton->show();
    bwboard->switch_map(mapname);
    bwboard->show();

    display2update = 1;
    update();
}

void blobwar::set_local_player_label(string color)
{
    local_player_label->set_text(color);
}

void blobwar::set_map_label(string filename)
{
    boardlabel->set_text(filename);
}

void blobwar::set_main_label(string text)
{
    mainlabel->set_text(text);
}

void blobwar::set_scores_label(string s)
{
    scoreslabel->set_text(s);
}

void blobwar::set_winner(Uint16 player)
{
    //delete all we don't need anymore
    delete bwrules;
    bwrules = NULL;
    //change displayed widgets
    bwboard->reset();
    bwboard->hide();
    scoreslabel->hide();
    mainlabel->hide();
    startgamebutton->hide();
    nextboardbutton->hide();
    previousboardbutton->hide();
    boardlabel->hide();
    local_player_label->hide();

    winner_images[player]->show();
    winlabel1->show();
    winlabel2->show();
    wingamebutton->show();
}

void blobwar::set_scores(Uint32 s1, Uint32 s2)
{
    stringstream s;
    s << "red player: " << s1;
    winlabel1->set_text(s.str());
    stringstream t;
    t << "blue player: " << s2;
    winlabel2->set_text(t.str());
}

/**
 * starts the games (mask board selection)
 * input is only needed in case of a network game (input is ID of local player)
 * */
void blobwar::start_game(Uint32 local_player_id)
{
    previousboardbutton->hide();
    startgamebutton->hide();
    nextboardbutton->hide();
    boardlabel->hide();
    bwboard->show();
    mainlabel->show();
    scoreslabel->show();
    if (local_player_id == 0)
    {
        set_local_player_label("you are : red");
        local_player_label->show();
    }
    else if (local_player_id == 1)
    {
        set_local_player_label("you are : blue");
        local_player_label->show();
    }
    new rules(gametype, bwboard, local_player_id);
    //activate selection if human player participates
    if (
        (gametype == GAME2P) ||
        (gametype == GAME1P) ||
        ((gametype == NETGAME) && (bwnet->get_player_type() == 0))
    )
    {
        bwboard->activate();
    }
}
