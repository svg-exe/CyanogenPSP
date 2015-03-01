#include "home.h"
#include "clock.h"
#include "lock.h"
#include "multi.h"
#include "power_menu.h"
#include "settingsmenu.h"
#include "screenshot.h"
#include "include/utils.h"

//variables
int result;
int notif_y = -272;
int yPos1 = -272;
int yPos2 = -272;
int yLine1 = -272;
int yLine2 = -272;
int controlX = 25;

void debugDisplay()
{
	debug = oslLoadImageFilePNG("system/debug/debug.png", OSL_IN_RAM, OSL_PF_8888);
	
	Roboto = oslLoadIntraFontFile("system/fonts/Roboto.pgf", INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
	oslSetFont(Roboto);
	
	while (!osl_quit)
	{	
		oslStartDrawing();

		controls();	
		
		oslIntraFontSetStyle(Roboto, 0.5f,BLACK,0,0);

		oslDrawImageXY(debug, 65, 67);
		oslDrawStringf(110,95,"Unfortunately some files required by");
		oslDrawStringf(110,110,"the program are missing. The program");
		oslDrawStringf(110,125,"has stopped, press (X) to exit to XMB.");

		if (osl_keys->pressed.cross)
		{
			sceKernelExitGame();
		}
	
		if (osl_pad.held.R && osl_keys->pressed.triangle) //Takes screenshot
		{
			screenshot();
		}
	
		oslEndDrawing(); 
		oslEndFrame(); 
		oslSyncFrame();
	}
}

void controls() //Main controller function - allows cursor movement
{
	//Intialize the limits
	int llimit = 0;
	int rlimit = 460;
	int ulimit = 0;
	int dlimit = 252;
		
	//Read keys
	oslReadKeys();
		
	if(osl_keys->analogX >= 50)
		cursor->x+= osl_keys->analogX/30;
		
	if(osl_keys->analogX <= -50)
		cursor->x+=osl_keys->analogX/30;

	if(osl_keys->analogY >= 50)
		cursor->y+= osl_keys->analogY/30;
		
	if(osl_keys->analogY <= -50)
		cursor->y+= osl_keys->analogY/30;
		
	/* Prevents the cursor from going off screen */
	
	if (cursor->x <= llimit)
	{
		cursor->x = llimit;
	}
		
	else if (cursor->x >= rlimit)
	{
		cursor->x = rlimit;
	}
		
	if (cursor->y <= ulimit)
	{	
		cursor->y = ulimit;
	}
		
	else if (cursor->y >= dlimit)
	{
		cursor->y = dlimit;
	}
		
	//Touch tones
	if (osl_keys->pressed.cross) oslPlaySound(tone, 1);         
	// It loads the sound file defined in the tones variable  when the cross button is pressed, in channel 1.
}

void battery(int batx, int baty, int n) // Draws the battery icon depending on its percentage. 
{
	int batteryLife;
	
	batteryLife = scePowerGetBatteryLifePercent(); //Gets battery percentage
	
	if (batteryLife <= 99 && n == 0)
	{
		batx = 343;
		baty = 2;
		oslDrawStringf(360, 4,"%d%%",batteryLife);
	}
	else  if (batteryLife > 99 && n == 0)
	{
		oslDrawStringf(352, 4,"%d%%",batteryLife);
	}
	
	if (batteryLife <= 99 && n == 1)
	{
		batx = 375;
		baty = 2;
		oslDrawStringf(392, 4,"%d%%",batteryLife);
	}
	else  if (batteryLife > 99 && n == 1)
	{
		oslDrawStringf(384, 4,"%d%%",batteryLife);
	}
 
	if (batteryLife == 100)
		oslDrawImageXY(batt100,batx,baty);
	else if (batteryLife >80 && batteryLife <= 100) 
		oslDrawImageXY(batt80,batx,baty);
	else if (batteryLife >60 && batteryLife <= 80)
		oslDrawImageXY(batt60,batx,baty);
	else if (batteryLife >40 && batteryLife <= 60)
		oslDrawImageXY(batt40,batx,baty);
	else if (batteryLife >20 && batteryLife <= 40) 
		oslDrawImageXY(batt20,batx,baty);
	else if (batteryLife >10 && batteryLife <= 20)
		oslDrawImageXY(batt10,batx,baty);
	else if (batteryLife >0 && batteryLife <= 10)
		oslDrawImageXY(batt0,batx,baty);
			
	if (scePowerIsBatteryCharging() == 1) // If the battery's charging, draw the charging icon on the battery icon.
		oslDrawImageXY(battcharge,batx,baty);
}

void appDrawerIcon() //Draws the app drawer icon. Draws a different icon of the same size once hovered with the cursor.
{
	if (cursor->x  >= 215 && cursor->x  <= 243 && cursor->y >= 195 && cursor->y <= 230)
		oslDrawImageXY(ic_allapps_pressed,218,197);
	
	else
		oslDrawImageXY(ic_allapps,218,197);
}

void navbarButtons(int n) //Draws the navbar buttons in the bottom as seen on androids.
{		
	if (n == 1)
	{
		oslDrawImageXY(navbar, 109, 237);
		
		if (cursor->x  >= 144 && cursor->x  <= 204 && cursor->y >= 226 && cursor->y <= 271)
			oslDrawImageXY(backicon,109, 237); //If the cursor is moved onto/near the back icon, it displays the highlighted back icon, else it just draws the navbar.
	
		else
			oslDrawImageXY(navbar,109, 237);
		
		if (cursor->x  >= 205 && cursor->x  <= 271 && cursor->y >= 226 && cursor->y <= 271)
			oslDrawImageXY(homeicon,109, 237); //If the cursor is moved onto/near the back icon, it displays the highlighted back icon, else it just draws the navbar.
	
		else
			oslDrawImageXY(navbar,109, 237);
		
		if (cursor->x  >= 272 && cursor->x  <= 332 && cursor->y >= 226 && cursor->y <= 271)
			oslDrawImageXY(multicon,109, 237); //If the cursor is moved onto/near the back icon, it displays the highlighted back icon. else it just draws the navbar.
	
		else
			oslDrawImageXY(navbar,109, 237);
		}
	
	else if (n == 2)
	{
		if ((cursor->x  >= 444 && cursor->x  <= 480) && (cursor->y >= 19 && cursor->y <= 75))
		{
			oslDrawImageXY(multicon2, 444, 19); //If the cursor is moved onto/near the back icon, it displays the highlighted back icon, else it just draws the navbar.
		}
	
		else if ((cursor->x  >= 444 && cursor->x  <= 480) && (cursor->y >= 157 && cursor->y <= 213))
		{
			oslDrawImageXY(backicon2, 444, 19); //If the cursor is moved onto/near the back icon, it displays the highlighted back icon. else it just draws the navbar.
		}

		else if ((cursor->x  >= 444 && cursor->x  <= 480) && (cursor->y >= 76 && cursor->y <= 155))
		{
			oslDrawImageXY(homeicon2, 444, 20); //If the cursor is moved onto/near the back icon, it displays the highlighted back icon, else it just draws the navbar.
		}
		else
		{
			oslDrawImageXY(navbar2, 444, 19);
		}
	}
}

void androidQuickSettings()
{
	SceCtrlData pad;

	int notif_up;
	int notif_down;
	int notif_enabled;
	
	int llimit = 20;
	int rlimit = 420;
	
	oslDrawImageXY(quickSettings,0,notif_y);
	
	battery(374,yPos2-2,2);
	getDayOfWeek(10,yPos2+5,1);
	getMonthOfYear(85,yPos2+5);

	oslDrawStringf(137,yLine1, "Wi-Fi");
	oslDrawStringf(340,yPos2, "%d%%",scePowerGetBatteryLifePercent());
	oslDrawStringf(292,yLine1, "Balanced");
		
	oslDrawStringf(202,yLine2, "Lockscreen");
	
	oslDrawImageXY(control,controlX,yPos2+66);	
		
	digitaltime(10,yPos1,48);
	
	if (getBrightness() == 10)
	{
		controlX = 20;
	}
	else if (getBrightness() == 20)
	{
		controlX = 70;
	}
	else if (getBrightness() == 30)
	{
		controlX = 120;
	}
	else if (getBrightness() == 40)
	{
		controlX = 170;
	}
	else if (getBrightness() == 50)
	{
		controlX = 220;
	}
	else if (getBrightness() == 60)
	{
		controlX = 270;
	}
	else if (getBrightness() == 70)
	{
		controlX = 320;
	}
	else if (getBrightness() == 80)
	{
		controlX = 370;
	}
	else if (getBrightness() == 90)
	{
		controlX = 420;
	}
		
	//This was in while (1) {}
	int amt = getBrightness();
	
	if (amt < 10) 
	{
		setBrightness(10);
	}

	if (amt > 90) 
	{
		setBrightness(90);
	}
	
	if (controlX <= llimit)
	{
		controlX = llimit;
	}
	else if (controlX >= rlimit)
	{
		controlX = rlimit;
	}
	
	notif_enabled = 0;
	
	if (osl_pad.held.cross && cursor->x >= 0 && cursor->x <= 480 && cursor->y >= 0 && cursor->y <= 1) 
	{
		notif_down = 1;
	}

	else if (osl_pad.held.cross && cursor->x >= 0 && cursor->x <= 480 && cursor->y >= 250 && notif_y == 0)
	{
		notif_up = 1;
	}
			
	if (notif_down == 1)
	{				
		if (osl_pad.held.cross && osl_keys->analogY >= 50)
		{
			notif_y = notif_y+6;
			yPos1 = yPos1+6;
			yPos2 = yPos2+6;
			yLine1 = yLine1+6;
			yLine2 = yLine2+6;
		}
		
		if (notif_y >= 0)
		{
			notif_y = 0;
		}
		
		if (yPos1 >= 10)
		{
			yPos1 = 10;
		}
		if (yPos2 >= 20)
		{
			yPos2 = 20;
		}
		if (yLine1 >= 180)
		{
			yLine1 = 180;
		}
		if (yLine2 >= 245)
		{
			yLine2 = 245;
		}
		if (yLine2 >= 200)
		{
			notif_enabled = 1;
		}
	}
	
	if (notif_enabled ==1)
		{
		if (osl_keys->held.up)
		{
			controlX += 4;
			setBrightness(getBrightness() + 1);
		}
		if (osl_keys->held.down)
		{
			controlX -= 4;
			setBrightness(getBrightness() - 1);
		}	
		
		if (cursor->x >= 386 && cursor->x <= 414 && cursor->y >= 12 && cursor->y <= 38 && osl_keys->pressed.cross)
		{	
			notif_y = notif_y-272;
			yPos1 = yPos1-272;
			yPos2 = yPos2-272;
			yLine1 = yLine1-272;
			yLine2 = yLine2-272;
			settingsMenu();
		}
	
		if (cursor->x >= 96 && cursor->x <= 206 && cursor->y >= 126 && cursor->y <= 192 && osl_keys->pressed.cross)
		{	
			notif_y = notif_y-272;
			yPos1 = yPos1-272;
			yPos2 = yPos2-272;
			yLine1 = yLine1-272;
			yLine2 = yLine2-272;
			wifiMenu();
		}
		
		if (cursor->x >= 198 && cursor->x <= 272 && cursor->y >= 204 && cursor->y <= 258 && osl_keys->pressed.cross)
		{	
			notif_y = notif_y-272;
			yPos1 = yPos1-272;
			yPos2 = yPos2-272;
			yLine1 = yLine1-272;
			yLine2 = yLine2-272;
			lockscreen();
		}
	}
	if (notif_down == 1 && osl_keys->pressed.circle)
	{
		notif_y = notif_y-272;
		yPos1 = yPos1-272;
		yPos2 = yPos2-272;
		yLine1 = yLine1-272;
		yLine2 = yLine2-272;
	}
	
	if (notif_up == 1)
	{		
		notif_enabled = 0;
		
		if (osl_pad.held.cross && osl_keys->analogY <= -50)
		{
			notif_y = notif_y-6;
			yPos1 = yPos1-6;
			yPos2 = yPos2-6;
			yLine1 = yLine1-6;
			yLine2 = yLine2-6;
		}
		
		if (notif_y <= -272)
		{	
			notif_y = -272;
			yPos1 = -272;
			yPos2 = -272;
			yLine1 = -272;
			yLine2 = -272;
		}
	}
}

void notif_2()
{
	while(!osl_quit)
	{
		oslStartDrawing();
		oslCopyImageTo(notif,notif2);	
		oslEndDrawing();
        oslEndFrame(); 
		oslSyncFrame();	
	}
}

void loadIcons() // Loading the app drawer icons.
{
	ic_allapps = oslLoadImageFilePNG("system/framework/framework-res/res/drawable-hdpi/ic_allapps.png", OSL_IN_RAM, OSL_PF_8888);
	ic_allapps_pressed = oslLoadImageFile("system/framework/framework-res/res/drawable-hdpi/ic_allapps_pressed.png", OSL_IN_RAM, OSL_PF_8888);
}

void unloadIcons() //Deleting the app drawer icons to save memory.
{
	oslDeleteImage(ic_allapps);
	oslDeleteImage(ic_allapps_pressed);
	oslDeleteFont(Roboto);
}

void LowMemExit() //This is temporary until I come up with a solution. It exits the app, once the memory is less than/equal to 1.5 MB
{
	if (oslGetRamStatus().maxAvailable <= 1500000)
	{
		oslQuit();
	}
}

void dayNightCycleWidget()
{
	pspTime time;
	sceRtcGetCurrentClockLocalTime(&time);
	
	if (time.hour > 12)
		time.hour -= 12;
	
	if (time.hour == 00)
		time.hour = 12;
		
    oslIntraFontSetStyle(Roboto, 1.7f,WHITE,0,INTRAFONT_ALIGN_CENTER);
	oslDrawStringf(235,70,"%2d:%02d", time.hour, time.minutes);
		
	oslIntraFontSetStyle(Roboto, 0.4f,WHITE,0,INTRAFONT_ALIGN_CENTER);
	getMonthOfYear(302,102);
	getDayOfWeek(196,102,2);
	
	if (time.hour < 6)
	oslDrawImageXY(wDay, 210, 82);
	
	else
	oslDrawImageXY(wNight, 205, 82);
}

void checkWidgetActivation()
{
	FILE * widgetActivation;

	if (!(fileExists("system/widget/widgetactivator.txt")))
	{
		widgetActivation = fopen("system/widget/widgetactivator.txt", "w");
		fprintf(widgetActivation, "1");
		fclose(widgetActivation);
	}

	widgetActivation = fopen("system/widget/widgetactivator.txt", "r");
	fscanf(widgetActivation,"%d",&widgetActivator);
	fclose(widgetActivation);
}

void homeUnloadResources()
{
	oslDeleteImage(ic_allapps);
	oslDeleteImage(ic_allapps_pressed);
	oslDeleteImage(wDay);
	oslDeleteImage(wNight);
	oslDeleteFont(Roboto);
}

void home()
{	
	loadIcons();
	wDay = oslLoadImageFilePNG("system/widget/Day.png", OSL_IN_RAM, OSL_PF_8888);
	wNight = oslLoadImageFile("system/widget/Night.png", OSL_IN_RAM, OSL_PF_8888);
	
	Roboto = oslLoadIntraFontFile("system/fonts/Roboto.pgf", INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
	oslSetFont(Roboto);
	
	checkWidgetActivation();
	
	while (!osl_quit)
	{
		LowMemExit();
		
		oslStartDrawing();

		controls();	
		
		oslDrawImage(background);	
		oslDrawImageXY(music, 105, 190);
		oslDrawImageXY(browser, 276, 190);
		oslDrawImageXY(gmail, 331, 190);
		oslDrawImageXY(messengericon, 160, 190);
		oslDrawImageXY(pointer, 232, 180);
		
		appDrawerIcon();
		navbarButtons(1);
		if (widgetActivator == 1)
		dayNightCycleWidget();
		
		oslIntraFontSetStyle(Roboto, 0.5f,WHITE,0,0);
		digitaltime(420,4,458);
		battery(370,2,1);
		androidQuickSettings();
		oslDrawImage(cursor);
			
		if (osl_keys->pressed.square)
		{
			powermenu();
		}

		if (cursor->x >= 276 && cursor->x <= 321 && cursor->y >= 195 && cursor->y <= 240 && osl_keys->pressed.cross)
		{
			homeUnloadResources();
			internet();
		}
		
		if (cursor->x >= 330 && cursor->x <= 374 && cursor->y >= 190 && cursor->y <= 240 && osl_keys->pressed.cross)
		{
			homeUnloadResources();
			openGmail();
		}
		
		if (cursor->x >= 100 && cursor->x <= 154 && cursor->y >= 195 && cursor->y <= 240 && osl_keys->pressed.cross)
		{
			homeUnloadResources();
			mp3player();
		}
		
		/*
		if (cursor->x >= 155 && cursor->x <= 210 && cursor->y >= 195 && cursor->y <= 240 && osl_keys->pressed.cross)
		{
			homeUnloadResources();
			messenger();
		}
		*/
			
		if (cursor->x >= 215 && cursor->x <= 243 && cursor->y >= 195 && cursor->y <= 230 && osl_keys->pressed.cross)
		{
			homeUnloadResources();
			appdrawer();
		}

		if (osl_keys->pressed.L)
		{	
			lockscreen();
        }
		
		if (cursor->x >= 276 && cursor->x <= 340 && cursor->y >= 237 && cursor->y <= 271 && osl_keys->pressed.cross)
		{
			multitask();
		}
		
		if (osl_pad.held.R && osl_keys->pressed.triangle)
		{
			screenshot();
		}
	
	oslEndDrawing(); 
    oslEndFrame(); 
	oslSyncFrame();
	}
}

