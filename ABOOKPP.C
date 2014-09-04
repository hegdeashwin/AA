/*
	PROJECT TITLE	:	ADDRESS BOOK ++
	SOFTWARE VERSION:	1.0.0.0 - WINDOWS VERSION.
	SOFTWARE LICENSE:	OPEN SOURCE
	COMPILED ON	:	TURBOC++ / DEV C++
	OS		:	MICROSOFT(R) WINDOWS

	DEVELOPERS	:	ASHWIN M. HEGDE
	WEBSITE		:	http://www.globalcodes.net
	FEEDBACK	:	webmaster@globalcodes.net
	EMAIL		:	intel_cracker@yahoo.com/hotmail.com
	FRONTEND TOOL	:	ANSI C
	BACKEND TOOL    :       *.abd (Address Book Data)
				 -> ORIGINAL DATAS AND INFORMATIONS.

				*.abs (Address Book Security)
				 -> SECURITY FILE.

				*.abp (Address Book Password)
				 -> PASSWORD FILE.

				*.abu (Address Book backUp)
				 -> BACKUP DATAS AND INFORMATIONS.

				*.abl (Address Book License)
				 -> ADDRESS BOOK LICENSE AGREEMENT.

				*.abi (Address Book Information);
				 -> ALL SECURITY INFORMATION.
*/

/* INCLUDE ALL REQUIRED FILES */
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <dos.h>
#include <process.h>
#include <time.h>

/* GLOBAL VARIABLES */
int flag,i,j,str,ac,oc,oldsize,access;
FILE *lic;
char choice,*pass,*rpass,*adminpass,*admin,*security,*opass,*oadmin;
struct date d;
struct time t;

/* DEFINED STRUCTURE  */
struct pone	// STRUCTURE FOR PERSONAL INFORMATION.
{
	char first[20];
	char middle[20];
	char last[20];
};
struct ptwo	// STRUCTURE FOR OTHER INFORMATION.
{
	char address[100];
	char gender;
};
struct pthree	// STRUCTURE FOR OTHER INFORMATION.
{
	char nick[20];
	char phoneno[20];
	char mobile[20];
};
struct business	// STRUCTURE FOR BUSINESS INFORMATION.
{
	char bcomp[100];
	char bjob[100];
	char bdepart[100];
};

/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int midx, midy,bkcol=10;
int left, top, right, bottom, xmax, ymax;

/* DECLARATION OF MODULE FUNCTIONS */
void progressbar();	// DRAW PROGRESSBAR SCREEN.
void screen();		// DRAW RECTANGLE SCREEN.
void dlscreen();	// DRAW DOUBLE RECTANGLE SCREEN.
void mainmenu();    	// MAIN MENU CHOICE.
void checklicense(); 	// CHECK WEATHER END USER HAS AGREE THE LICENSE TERMS.
void agreement();   	// SOFTWARE LICENSE AGREEMENT.
void err(int ecode,int menuno); // ERROR HANDLER FOR MENU AND VALIDATION.
void errorscreen(int eno);	// ERROR HANDLER FOR SECURITY CHECKS.
void contactmenu(); 	// MAIN SUB MENU FOR CHOICE CONTACTS.
void backupdata();	// BACKUP DATABASE.
void securitymenu();    // SUB MENU FOR CHOICE SECURITY.
void administrator();	// ADMINISTRATOR PASSWORD SECURITY.
void aboutus();    	// AUTHORS INFORMATION.
void help();	    	// HELP INFORMATION.
void add();   		// ADD NEW CONTACTS.
void datavalidation(); 	// INPUT DATA VALIDATIONS.
void view();		// VIEW AND LIST ALL CONTACTS.
void upsecurity();	// UPDATE SECURITY.
void resecurity();	// REMOVE SECURITY.
void tracesecurityerror(); // TRACE LOGIN SECURITY FAILED.
void logfile();		// VIEW LOG FILES.

//  MAIN PROGRAM BEGINS.
int main()
{
	clrscr();
	progressbar();

	// CHECK security.abs FILE EXIST.
	lic = fopen("security.abs","r");
	if(lic == NULL)
	{
		// FILE DOES NOT EXIST.
		lic = fopen("security.abs","w");
		fprintf(lic,"nosecurity");
		fclose(lic); flushall();
		checklicense();
	}
	else
	{
		// FILE EXIST.
		// CHECK ITS VALUES.
		// VALUE = SECURITY : INSTALLED SECURITY.
		// VALUE = NOSECURITY : NOT INSTALLED SECURITY.
		// ELSE SOME HAS TRYED TO BREAK INTO SECURITY.
		fscanf(lic,"%s",security);
		str = strcmp(security,"security");

		if(str == 0)
		{
			// VALUE = SECURITY
			// SO, SECURITY HAS BEEN INSTALLED.
			// SO, PASSWORD FILE EXIST.
			lic = fopen("ritybook.abp","r");
			if(lic != NULL)
			{
				// FILE EXIST.
				// CALL ADMINISTRATOR.
				administrator();
			}
			else
			{
				// FILE DOES NOT EXIST.
				errorscreen(1);
			}
		}
		else
		{
			// CHECK SECURITY VALUE FILE VALUES.
			fscanf(lic,"%s",security);
			str = strcmp(security,"nosecurity");
			if(str == 0)
			{
				// VALUE = NOSECURITY.

				// CHECK PASSWORD FILE EXIST.
				// IF YES THEN ACESS DENIED.
				// IF NO THEN CHECKLICENSE.
				lic = fopen("ritybook.abp","r");
				if(lic == NULL)
				{
					// PASSWORD FILE DOES NOT EXIST.
					// SO, SECURITY HAS NOT BEEN INSTALLED YET.
					checklicense();
				}
				else
				{
					// PASSWORD FILE EXIST.
					// SO, SECURITY HAS BEEN INSTALLED.
					// SOME ONE HAS DELETED PASSWORD FILE.
					// SO, ACCESS DENIED.
					fclose(lic); flushall();
					clrscr();
					/**/
					errorscreen(1);
				}
			}
			else
			{
				// VALUE = OTHER.
				clrscr();
				/**/
				errorscreen(1);
			}
		}
	}
	getch();
	return 0;
}
// MAIN PROGRAM ENDS.


/* DEFINATION OF MODULE FUNCTIONS */

// SCREEN DESIGNING MODULE STARTS.
void progressbar()
{
	clrscr();
	dlscreen();

	/* DRAW PROGRESSBAR */
	// PERCENT : 0%-20%   -->  MESSAGE : LOADING ADDRESS BOOK ++ ...
	// PERCENT : 20%-40%  -->  MESSAGE : LOADING DATABASE ...
	// PERCENT : 40%-60%  -->  MESSAGE : CONNECTING MODULES ...
	// PERCENT : 60%-80%  -->  MESSAGE : CONNECTING ESTABLISHED ...
	// PERCENT : 80%-100% -->  MESSAGE : DONE ...
	setcolor(7);
	gotoxy(8,3);
	printf("Welcome To Address Book ++");
	gotoxy(66,3);
	printf("V1.0.0.0");
	gotoxy(80/4,5);
	printf("G L O B A L C O D E S - S O F T W A R E S");
	line(80,80,540,80);
	gotoxy(80/4,7);
	printf("  w w w . g l o b a l c o d e s . n e t ");
	line(50,50,590,50);
	rectangle(600,300,30,315);

	delay(500);
	gotoxy(6,18); printf("LOADING: 0%");
	gotoxy(33,12); printf("ADDRESS BOOK ++");
	bar3d(50,300,30,315,0,0);
	delay(1000);

	gotoxy(6,18); printf("LOADING: 10%");
	gotoxy(31,12); printf("CONNECTING DATABASE");
	bar3d(50,300,30,315,0,0);
	delay(500);

	gotoxy(6,18); printf("LOADING: 20%");
	gotoxy(31,12); printf("CONNECTING DATABASE .");
	bar3d(120,300,30,315,0,0);
	delay(2000);

	gotoxy(6,18); printf("LOADING: 30%");
	gotoxy(31,12); printf("CONNECTING DATABASE ...");
	bar3d(190,300,30,315,0,0);
	delay(500);

	gotoxy(6,18); printf("LOADING: 40%");
	gotoxy(31,12); printf("CONNECTING MODULES ");
	bar3d(250,300,30,315,0,0);
	delay(500);

	gotoxy(6,18); printf("LOADING: 50%");
	gotoxy(31,12); printf("CONNECTING MODULES .");
	bar3d(310,300,30,315,0,0);
	delay(2000);

	gotoxy(6,18); printf("LOADING: 60%");
	gotoxy(31,12); printf("CONNECTING MODULES ...");
	bar3d(370,300,30,315,0,0);
	delay(500);

	gotoxy(6,18); printf("LOADING: 70%");
	gotoxy(31,12); printf("CONNECTION ESTABLISHED .");
	bar3d(430,300,30,315,0,0);
	delay(500);

	gotoxy(6,18); printf("LOADING: 80%");
	gotoxy(29,12); printf("CONNECTION ESTABLISHED ...");
	bar3d(500,300,30,315,0,0);
	delay(2000);

	gotoxy(6,18); printf("LOADING: 90%");
	gotoxy(28,12); printf("UPDATING SECURITY SETTINGS");
	bar3d(570,300,30,315,0,0);
	delay(3000);

	gotoxy(6,18); printf("LOADING: 100%");
	gotoxy(28,12); printf("WELCOME TO ADDRESS BOOK ++ ");
	bar3d(600,300,30,315,0,0);
	delay(500);

	/*clear the screen*/
	cleardevice();
	closegraph();
}

void screen()
{
	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	left = getmaxx() / 2 - 310;
	top = getmaxy() / 2 - 220;
	right = getmaxx() / 2 + 310;
	bottom = getmaxy() / 2 + 180;
	/* draw a inner rectangle */
	setcolor(14);
	rectangle(left,top,right,bottom);
}

void dlscreen()
{
	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	left = getmaxx() / 2 - 310;
	top = getmaxy() / 2 - 220;
	right = getmaxx() / 2 + 310;
	bottom = getmaxy() / 2 + 180;
	/* draw a inner rectangle */
	setcolor(14);
	rectangle(left,top,right,bottom);

	left = getmaxx() / 2 - 314;
	top = getmaxy() / 2 - 224;
	right = getmaxx() / 2 + 314;
	bottom = getmaxy() / 2 + 185;
	/* draw a outer rectangle  */
	rectangle(left,top,right,bottom);
}

void errorscreen(int eno)
{
	/*
		ERROR NO --> DIRECT MEANING
		1 --> ACCESS DENIED
		2 --> AUTHENTICATION FAILED
	*/

	clrscr();
	gotoxy(2,2);
/**/
	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	setcolor(getmaxcolor());
	/* for centering screen messages */
	settextjustify(CENTER_TEXT, CENTER_TEXT);

	if(eno == 1)
	{
		setcolor(4);
		setbkcolor(15);
		tracesecurityerror(1);
		/* output a message to the screen */
		outtextxy(midx, midy, "Security Error! : ACCESS-DENIED");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		exit(0);
	}
	else if(eno == 2)
	{
		setcolor(4);
		setbkcolor(15);
		tracesecurityerror(2);
		/* output a message to the screen */
		outtextxy(midx, midy, "Security Error! : AUTHENTICATION-FAILED.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		exit(0);
	}
}
// SCREEN DESIGNING MODULE ENDS.

// CHECK ADMINISTRATOR PASSWORD INSTALLED MODULE START.
void administrator()
{
	getdate(&d);
	clrscr();
	dlscreen();
	gotoxy(80/6,3);
	printf("WELCOME TO ADDRESS BOOK ++  [ ACCESS LEVEL SECURITY ]."); // GET USER NAME.
	gotoxy(80/8,8);
	printf("You Can't See The Password, So Just Relax And Type Your Password");
	gotoxy(1,4);
	printf("--------------------------------------------------------------------------------");
	gotoxy(80/4,11);
	printf("-----------------------------------");
	gotoxy(32,20);
	printf("%d - %d - %d",d.da_day,d.da_mon,d.da_year);
	gotoxy(80/4,10);
	adminpass = getpass("Enter Password To Unlock The System\n");
	gotoxy(80/3,12);

	// GET PASSWORD FROM FILE AND CHECK IT.
	lic = fopen("ritybook.abp","r");
	fscanf(lic,"%s",admin);

	ac = strcmp(adminpass,admin);
	if(ac == 0)
	{
		// PASSWORD ARE EQUAL.
		// AUTHENTICATION SUCCESSFUL.
		gotoxy(80/5,15);
		printf("A U T H E N T I C A T I O N - S U C C E S S F U L");
		getch();
		checklicense(); // CHECK WEATHER USER HAS, ACCEPTED SOFTWARE LICENSE.
	}
	else
	{
		// PASSWORD ARE NOT EQUAL.
		// AUTHENTICATION FAILED.
		errorscreen(2);
	}
}
// ADMINISTRATOR PASSWORD INSTALLED MODULE END.

// CHECK LICENSE MODULE START.
void checklicense()
{
	lic=fopen("license.abl","r");
	if(lic==NULL)
	{
		// FILE DOES NOT EXIST.
		// SO CALL AGREEMENT.
		agreement();
	}
	else
	{
		// FILE EXIST. AND USER HAS AREADY
		// ACCEPTED THE SOFTWARE LICENSE.
		// SO CALL PROGRAM MAIN MENU.
		clrscr();
		fclose(lic); flushall();
		mainmenu();
	}
}
// CHECK LICENSE MODULE END.

// MENU CHOICE MODULE STARTS.
void mainmenu()
{
	int r;
	clrscr();
	dlscreen();

	gotoxy(80/20,3);
	printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
	gotoxy(80/20,4);
	printf("-----------------------------------------------------");
	gotoxy(80/20,5);
	printf(" ");
	gotoxy(80/20,6);
	printf("  1. Contacts.             (Press `C` or `c`)\n");
	gotoxy(80/20,8);
	printf("  2. Backup All Data.      (Press `B` or `b`)\n");
	gotoxy(80/20,10);
	printf("  3. Security.             (Press `S` or `s`)\n");
	gotoxy(80/20,12);
	printf("  4. Security Logs.        (Press `L` or `l`)\n");
	gotoxy(80/20,14);
	printf("  5. Help.                 (Press `H` or `h`)\n");
	gotoxy(80/20,16);
	printf("  6. About Address book++  (Press `A` or `a`)\n");
	gotoxy(80/20,18);
	printf("  7. Terminate Program.    (Press `T` or `t`)\n");
	gotoxy(80/20,20);
	printf("----------------------------------------------------");
	gotoxy(80/20,21);
	printf("  Enter Your Choice : ");
	gotoxy(80/20,22);
	printf("----------------------------------------------------");

	choice = getch();

	if(choice == 'c' || choice == 'C')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		contactmenu();
	}
	else if(choice == 'b' || choice == 'B')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		backupdata();
	}
	else if(choice == 's' || choice == 'S')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		securitymenu();
	}
	else if(choice == 'l' || choice == 'L')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		logfile();
	}
	else if(choice == 'h' || choice == 'H')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		help();
	}
	else if(choice == 'a' || choice == 'A')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		aboutus();
	}
	else if(choice == 't' || choice == 'T')
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		clrscr();
		dlscreen();

		gotoxy(80/20,3);
		printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
		gotoxy(80/20,4);
		printf("-----------------------------------------------------");
		gotoxy(80/20,5);
		printf(" ");
		gotoxy(80/20,6);
		printf("  ARE YOU SURE YOU WANT TO QUIT THE PROGRAM!");
		gotoxy(80/20,8);
		printf("  PRESS `Y|y` TO EXIT / PRESS ANY KEY TO CONTINUE ...");
		gotoxy(80/20,10);
		printf("  CONFIRMATION : ");
		r = getch();

		if(r == 'y' || r == 'Y')
		{
			// SURE TO EXIT.
			/* clear the screen */
			cleardevice();
			closegraph();
			exit(0);
		}
		else
		{
			// NOT SURE TO EXIT.
			/* clear the screen */
			cleardevice();
			closegraph();
			mainmenu();
		}
	}
	else
	{
		clrscr();
		/* clear the screen */
		cleardevice();
		closegraph();
		err(1,1);
	}
}
// MENU CHOICE MODULE ENDS.

// AGREEMENT LICENSE MODULE STARTS.
void agreement()
{
	int agree;
	screen();

	gotoxy(80/8,3);
	printf("Please Read The License Terms Of The Software Before Using It.");
	gotoxy(80/20,4);
	printf("--------------------------------------------------------------------------");
	gotoxy(80/20,5);
	printf(" This file is part of K. K. Wagh Institute Of Engineering Education");
	gotoxy(80/20,6);
	printf(" and Research, F E M C A (Engineering) Project.");
	gotoxy(80/20,8);
	printf(" `Address Book ++` is free software:");
	gotoxy(80/20,9);
	printf(" You can redistribute it and/or modify it under terms of GNU General");
	gotoxy(80/20,10);
	printf(" Public License as published by Free Software Foundation, either");
	gotoxy(80/20,11);
	printf(" version 3 of the license, or (at your option) any later version.");
	gotoxy(80/20,12);
	printf(" ");
	gotoxy(80/20,13);
	printf(" `Address Book ++` is distributed in the hope that it will be useful");
	gotoxy(80/20,14);
	printf(" but WITHOUT WARRANTY without even the implied warranty of ");
	gotoxy(80/20,15);
	printf(" MERCHANTABILITY or FITNESS for a particular purpose. See the GNU");
	gotoxy(80/20,16);
	printf(" General Public License for more details.");
	gotoxy(80/20,17);
	printf(" You should have a received a copy of the GNU General Public");
	gotoxy(80/20,18);
	printf(" License along with `Address Book ++`.");
	gotoxy(80/20,20);
	printf(" If not, please visit:- http://www.gnu.org/license/");
	gotoxy(80/20,21);
	printf(" BY PROGRAM AUTHOR: ASHWIN M. HEGDE");
	gotoxy(80/20,23);
	textcolor(7);
	printf("------------------------- AGREEMENT CONFIRMATION -------------------------");
	gotoxy(80/8,24);
	printf(" ");
	gotoxy(80/8,25);
	printf(" DO YOU AGREE WITH ALL TERMS AND CONDITIONS (PRESS `Y` OR `y`):   ");

	agree = getch();
	fflush(stdin);

	if(agree=='y' || agree=='Y')
	{
		// YES I AGREE ALL THE TERMS AND CONDITIONS.
		// END USER ACCEPTED LICENSE AGREEMENT,
		// SO CAN USE THE SOFTWARE FREELY.
		lic = fopen("license.abl","w");
		fprintf(lic,"Please Read The License Terms Of The Software Before Using It.");
		fprintf(lic,"--------------------------------------------------------------------------");
		fprintf(lic," This file is part of K. K. Wagh Institute Of Engineering Education");
		fprintf(lic," and Research, F E M C A (Engineering) Project.");
		fprintf(lic," `Address Book ++` is free software:");
		fprintf(lic," You can redistribute it and/or modify it under terms of GNU General");
		fprintf(lic," Public License as published by Free Software Foundation, either");
		fprintf(lic," version 3 of the license, or (at your option) any later version.");
		fprintf(lic," ");
		fprintf(lic," `Address Book ++` is distributed in the hope that it will be useful");
		fprintf(lic," but WITHOUT WARRANTY without even the implied warranty of ");
		fprintf(lic," MERCHANTABILITY or FITNESS for a particular purpose. See the GNU");
		fprintf(lic," General Public License for more details.");
		fprintf(lic," You should have a received a copy of the GNU General Public");
		fprintf(lic," License along with `Address Book ++`.");
		fprintf(lic," If not, please visit:- http://www.gnu.org/license/");
		fprintf(lic," BY PROGRAM AUTHOR: ASHWIN M. HEGDE");
		fclose(lic); flushall();
		/* clear the screen */
		cleardevice();
		closegraph();
		mainmenu();
	}
	else
	{
		// NO I DO NOT AGREE ALL THE TERMS AND CONDITIONS.
		// END USER DID NOT ACCEPTED LICENSE AGREEMENT,
		// SO CAN NOT USE THE SOFTWARE.
		clrscr();

		// DELETE SECURITY FILE.
		remove("security.abs");

		/**/
		/* initialize graphics and local variables */
		initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
		/* read result of initialization */
		errorcode = graphresult();
		if (errorcode != grOk)  /* an error occurred */
		{
			printf("Graphics error: %s\n", grapherrormsg(errorcode));
			printf("Press any key to halt:");
			getch();
			exit(1); /* terminate with an error code */
		}

		midx = getmaxx() / 2;
		midy = getmaxy() / 2;
		setcolor(getmaxcolor());

		/* for centering screen messages */
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setcolor(4);
		setbkcolor(15);
		/* output a message to the screen */
		outtextxy(midx, midy, "Terminating The Program");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		exit(0);
	}
}
// AGREEMENT LICENSE MODULE ENDS.

// ERROR HANDLER FOR VALIDATION AND MENU MODULE START.
void err(int ecode,int menuno)
{
	/* ERROR CODE NO. --> 	ERROR MESSAGE.

		1 	  -->   INVALID MENU CHOICE.
		2	  -->   PASSWORD MISMATCH.
		3	  -->	ACCESS DENIED.


	-------------------------------------------------------
	   MENU CODE NO. -->   MENU NAME.

		1	 -->	MAIN MENU.
		2	 -->	CONTACTS MENU.
		3	 -->	BACKUP DATABASE MENU.
		4	 -->	SECURITY MENU.

	*/

	clrscr();
	gotoxy(2,2);
/**/
	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		 exit(1); /* terminate with an error code */
	}

	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	setcolor(getmaxcolor());
	/* for centering screen messages */
	settextjustify(CENTER_TEXT, CENTER_TEXT);

	if(ecode == 1 && menuno == 1)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Invalid Choice Entry.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();

		mainmenu();
	}
	else if(ecode == 1 && menuno == 2)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Invalid Choice Entry.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		contactmenu();
	}
	else if(ecode == 1 && menuno == 3)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Invalid Choice Entry.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		securitymenu();
	}
	else if(ecode == 1 && menuno == 4)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Invalid Choice Entry.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}
	else if(ecode == 2 && menuno == 4)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Password Are Not Matching.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		securitymenu();
	}
	else if(ecode == 2 && menuno == 5)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Password Length Must Be Min 4 And Max 8 Character Long.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		securitymenu();
	}
	else if(ecode == 2 && menuno == 6)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Error! : Password Can Not Be Blank.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		securitymenu();
	}
	else if(ecode == 3 && menuno == 5)
	{
		/* output a message to the screen */
		outtextxy(midx, midy, "Security Error! : Access Denied - Invalid Password");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		securitymenu();
	}
}
// ERROR HANDLER MODULE ENDS.

// CONTACT SUB MENU DESIGN MODULE START.
void contactmenu()
{
	clrscr();
	dlscreen();

	gotoxy(80/20,3);
	printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
	gotoxy(80/20,4);
	printf("-----------------------------------------------------");
	gotoxy(80/20,5);
	printf(" Contacts.             (Press `C` or `c`)");
	gotoxy(80/20,7);
	printf("      1. Add New Contact.    (Press `A` or `a`)");
	gotoxy(80/20,9);
	printf("      ");
	gotoxy(80/20,11);
	printf("      2. List All View.      (Press `V` or `v`)");
	gotoxy(80/20,15);
	printf("----------------------------------------------------");
	gotoxy(80/20,18);
	printf("  Enter Your Choice : ");
	gotoxy(80/20,19);
	printf("----------------------------------------------------");

	choice = getch();

	if(choice == 'c' || choice == 'C')
	{
		// CALL MAIN MENU.
		/* clear the screen */
		cleardevice();
		closegraph();
		mainmenu();
	}
	else if(choice == 'a' || choice == 'A')
	{
		// ADD NEW CONTACT.
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}
	else if(choice == 'v' || choice == 'V')
	{
		// LIST ALL VIEW.
		/* clear the screen */
		cleardevice();
		closegraph();
		view();
	}
	else
	{
		/* clear the screen */
		cleardevice();
		closegraph();
		clrscr();
		err(1,2);
	}
}
// CONTACT SUB MENU DESIGN MODULE ENDS.

// SECURITY SUB MENU DESIGN MODULE START.
void securitymenu()
{
	clrscr();
	dlscreen();

	// CHECK SECURITY FILE EXIST.
	lic = fopen("ritybook.abp","r");
	if(lic == NULL)
	{
		// FILE DOES NOT EXIST.
		// SO CALL AGREEMENT.
		// FIRST SECURITY INSTALLATION.
		// CREATE SECURITY FILE.

		gotoxy(80/20,3);
		printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
		gotoxy(80/20,4);
		printf("--------------------------------------------------------------");
		gotoxy(80/20,5);
		printf(" [1] Password Must Be Between Min 4 And Max 8 Characters Long.");
		gotoxy(80/20,6);
		printf(" [2] Password Must Be Strong (Space Is Not Allowed).");
		gotoxy(80/20,7);
		printf(" [3] Space Is Not Allowed In Password If Did,");
		gotoxy(80/20,8);
		printf("     Rest After Space Will Be Ignored.");
		gotoxy(80/20,9);
		printf(" [4] You Can't See The Password, So Just Type It.");
		gotoxy(80/20,12);
		pass = getpass(" Enter New Password : ");

		if(strlen(pass) == 0)
		{
			//INVALID PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,6);
		}
		if(strlen(pass) < 4 || strlen(pass) > 8)
		{
			// INVALID PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,5);
		}
		gotoxy(80/20,14);
		rpass = getpass(" Re-Enter Password  : ");
		if(strlen(rpass) == 0)
		{
			// INVALID REENTER PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,6);
		}
		if(strlen(rpass) < 4 || strlen(rpass) > 8)
		{
			// INVALID PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,5);
		}
		// CHECK PASSWORD AND CONFIRM PASSWORD MATCH.
		str = strcmp(pass,rpass);
		if(str == 0)
		{
			// PASSWORD MATCH.
			// SAVE THIS PASSWORD IN FILE.

			gotoxy(80/4,18);
			printf("Your Password Has Been Encrypted And Saved.");
			// INSTALL AND SAVED PASSWORD.
			lic = fopen("ritybook.abp","w");
			fprintf(lic,pass);
			fclose(lic); flushall();
			// INSTALL AND SAVE SECURITY FILE.
			// security = SECURITY HAS BEEN INSTALLED.
			// nosecurity = SECURITY IS NOT BEEN INSTALLED.
			lic = fopen("security.abs","w");
			fprintf(lic,"security");
			fclose(lic); flushall();
			getch();
			/* clear the screen */
			cleardevice();
			closegraph();
			mainmenu();
		}
		else
		{
			// PASSWORD MISMATCH.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,4);
		}
	}
	else
	{
		// FILE EXIST. AND USER HAS AREADY INSTALL SECURITY.
		// SO, SHOW SECURITY MENU.
		gotoxy(80/20,3);
		printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
		gotoxy(80/20,4);
		printf("-----------------------------------------------------");
		gotoxy(80/20,5);
		printf(" Security                (Press `S` or `s`)");
		gotoxy(80/20,7);
		printf("      1. Update Security.     (Press `U` or `u`)");
		gotoxy(80/20,9);
		printf("      2. Remove Security.     (Press `R` or `r`)");
		gotoxy(80/20,11);
		printf("----------------------------------------------------");
		gotoxy(80/20,13);
		printf("  Enter Your Choice : ");
		gotoxy(80/20,15);
		printf("----------------------------------------------------");

		choice = getch();
		fflush(stdin);

		if(choice == 's' || choice == 'S')
		{
			/* clear the screen */
			cleardevice();
			closegraph();
			mainmenu();
		}
		else if(choice == 'u' || choice == 'U')
		{
			// UPDATE SECURITY.
			/* clear the screen */
			cleardevice();
			closegraph();
			upsecurity();
		}
		else if(choice == 'r' || choice == 'R')
		{
			// REMOVE SECURITY.
			/* clear the screen */
			cleardevice();
			closegraph();
			resecurity();
		}
		else
		{
			clrscr();
			/* clear the screen */
			cleardevice();
			closegraph();
			err(1,3);
		}
	}
}       // SECURITY SUB MENU DESIGN MODULE ENDS.

// BACKUP MODULE START.
void backupdata()
{
	// BACK UP DATABASE.
}
// BACKUP MODULE START.

// HELP MODULE START.
void help()
{
	dlscreen();

	gotoxy(80/20,3);
	printf("HELP");
	gotoxy(80/20,4);
	printf("-------------------------------------------------------------------------");
	gotoxy(80/20,5);
	printf(" THANK YOU FOR USING OUR SOFTWARE.");
	gotoxy(80/20,6);
	printf(" ");
	gotoxy(80/20,7);
	printf(" SOFTWARE FEEDBACK: ");
	gotoxy(80/20,8);
	printf("   -->  http://www.globalcodes.net/ashwin_osp/feedback-me.php");
	gotoxy(80/20,9);
	printf(" " );
	gotoxy(80/20,10);
	printf(" WANT TO BE A MEMBER OF OUR SOFTWARE DEVELOPMENT PROJECTS, ");
	gotoxy(80/20,11);
	printf(" PLEASE REGISTER TO: ");
	gotoxy(80/20,12);
	printf("   -->  http://www.globalcodes.net/register-me.php");
	gotoxy(80/20,14);
	printf(" ------------------------- PLEASE VISIT ------------------------");
	gotoxy(80/20,15);
	printf("  WEBSITE  :--> http://www.globalcodes.net\n");
	gotoxy(80/20,16);
	printf("  FEEDBACK :--> webmaster@globalcodes.net\n");
	gotoxy(80/20,17);
	printf("  EMAIL	   :--> intel_cracker@yahoo.com/hotmail.com\n");
	gotoxy(80/20,18);
	printf(" ");
	gotoxy(80/20,19);
	printf(" ------------------------- ONLINE HELP -------------------------");
	gotoxy(80/20,20);
	printf("  http://www.globalcodes.net/ashwin-osp/pro-help-codes.php");

	/* clean up */
	getch();
	cleardevice();
	closegraph();

	mainmenu();
}
// HELP MODULE ENDS.

// ABOUT US MODULE START.
void aboutus()
{
	clrscr();
	dlscreen();

	gotoxy(80/20,3);
	printf("ABOUT ADDRESS BOOK ++");
	gotoxy(80/20,4);
	printf("-------------------------------------------------------------------------");
	gotoxy(80/20,5);
	printf("  PROJECT TITLE     : ADDRESS BOOK ++");
	gotoxy(80/20,6);
	printf("  SOFTWARE VERSION  : 1.0.0.0");
	gotoxy(80/20,7);
	printf("  SOFTWARE LICENSE  : OPEN SOURCE");
	gotoxy(80/20,8);
	printf("  ");
	gotoxy(80/20,9);
	printf("  SUPPORTED OS      : MICROSOFT WINDOWS(R)");
	gotoxy(80/20,10);
	printf("----------------------------------------------------------");
	gotoxy(80/20,11);
	printf("  DEVELOPER         : ASHWIN M. HEGDE\n");
	gotoxy(80/20,12);
	printf("                    : THANK YOU FOR USING OUR SOFTWARE.");
	gotoxy(80/20,13);
	printf("       ");
	gotoxy(80/20,14);
	printf("                    : Copyright(C) 2009-2010, Ashwin M. Hegde");
	gotoxy(80/20,15);
	printf("                    : All Right Reserver(R). Globalcodes");
	gotoxy(80/20,16);
	printf("       ");
	gotoxy(80/20,17);
	printf("----------------------------------------------------------");
	gotoxy(80/20,18);
	printf("  WEBSITE  : http://www.globalcodes.net\n");
	gotoxy(80/20,19);
	printf("  FEEDBACK : webmaster@globalcodes.net\n");
	gotoxy(80/20,20);
	printf("  EMAIL	   : intel_cracker@yahoo.com/hotmail.com\n");

	/* clean up */
	getch();
	cleardevice();
	closegraph();

	mainmenu();
}
// ABOUT US MODULE ENDS.

// ADD NEW CONTACT MODULE START.
void add()
{
	char choice,r;
	struct pone po;
	struct ptwo to;
	struct pthree pt;
	struct business bu;

	clrscr();
	dlscreen();

	gotoxy(80/20,3);
	printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
	gotoxy(80/20,4);
	printf("-----------------------------------------------------");
	gotoxy(80/20,5);
	printf(" PLEASE FILL UP THE FOLLOWING INFORMATION.");
	gotoxy(80/20,6);
	printf(" * Required Field Else Field Entry Is Optional.");
	gotoxy(80/20,10);
	printf("First Name* : "); gets(po.first); fflush(stdin);
	// CHECK FIRST NAME VALIDATION FOR REQUIRED FIELD.
	if(strlen(po.first) == 0)
	{
		// STRING IS A BLANK SPACE.
		// NOT POSSIBLE => REQUIRED FIELD.
		datavalidation(1);
	}
	else
	{
		// CHECK IT IS PURE STRING.
		for(i=0;i<strlen(po.first);i++)
		{
			if(isalpha(po.first[i]))
			{
				// IS A PURE STRING.
			}
			else
			{
				// NOT PURE STRING.
				datavalidation(3);
			}
		}
	}
	gotoxy(80/20,11);
	printf("Middle Name : "); scanf("%s",&po.middle); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(po.middle);i++)
	{
		if(isalpha(po.middle[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	}
	gotoxy(80/20,12);
	printf("Last Name   : "); scanf("%s",&po.last); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(po.last);i++)
	{
		if(isalpha(po.last[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	}
	gotoxy(80/20,13);
	printf("Nick Name   : "); scanf("%s",&pt.nick); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(pt.nick);i++)
	{
		if(isalpha(pt.nick[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	}
	gotoxy(80/20,14);
	printf("Address     : "); scanf("%[^\n]",&to.address); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(to.address);i++)
	{
		if(isalpha(to.address[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	}
	gotoxy(80/20,15);
	printf("Phone       : "); scanf("%s",&pt.phoneno); fflush(stdin);
	// CHECK IT IS PURE DIGIT.
	for(i=0;i<strlen(pt.phoneno);i++)
	{
		if(isdigit(pt.phoneno[i]))
		{
			// IS A PURE DIGIT.
		}
		else
		{
			// NOT PURE DIGIT.
			datavalidation(2);
		}
	}
	if(strlen(pt.phoneno) < 6 && strlen(pt.phoneno) > 11)
	{
		// INVALID PHONE NO.
		datavalidation(5);
	}

	gotoxy(80/20,16);
	printf("Mobile      : "); scanf("%s",&pt.mobile); fflush(stdin);
	// CHECK IT IS PURE DIGIT.
	for(i=0;i<strlen(pt.mobile);i++)
	{
		if(isdigit(pt.mobile[i]))
		{
			// IS A PURE DIGIT.
		}
		else
		{
			// NOT PURE DIGIT.
			datavalidation(2);
		}
	 }
	 if(strlen(pt.phoneno) < 10 && strlen(pt.phoneno) > 12)
	 {
		// INVALID PHONE NO.
		datavalidation(5);
	 }
	gotoxy(80/20,17);
	printf("Gender(M/F) : "); scanf("%c",&to.gender); fflush(stdin);
	if(to.gender == 'M' || to.gender == 'm' || to.gender == 'F' || to.gender == 'f')
	{
		// VALID GENDER.
	}
	else
	{
		datavalidation(4);
	}
	gotoxy(80/20,18);
	printf("Company Name: "); scanf("%[^\n]",&bu.bcomp); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(bu.bcomp);i++)
	{
		if(isalpha(bu.bcomp[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	 }
	gotoxy(80/20,19);
	printf("Job Title   : "); scanf("%[^\n]",&bu.bjob); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(bu.bjob);i++)
	{
		if(isalpha(bu.bjob[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	}
	gotoxy(80/20,20);
	printf("Department  : "); scanf("%[^\n]",&bu.bdepart); fflush(stdin);
	// CHECK IT IS PURE STRING.
	for(i=0;i<strlen(bu.bdepart);i++)
	{
		if(isalpha(bu.bdepart[i]))
		{
			// IS A PURE STRING.
		}
		else
		{
			// NOT PURE STRING.
			datavalidation(3);
		}
	}

	/* clean up */
	cleardevice();
	closegraph();
	/* VALIDATE INPUT DATA */
	// IF ALL INPUT DATA ARE VALID: SAVE IT.
	// ELSE SHOW ERROR.
	lic=fopen("BookData.abd","a+");
	// CALL RANDOM FUNCTION FOR ACCESS POINT VARIABLE.
	randomize();
	fprintf(lic,"%d %s %s %s %s %s %s %s %c %s %s %s\n",random(3000),po.first,po.middle,po.last,pt.nick,to.address,pt.phoneno,pt.mobile,to.gender,bu.bcomp,bu.bjob,bu.bdepart);
	contactmenu();
}
// SUB MODULE BUSINESS ENDS.

// VIEW CONTACT MODULE START.
void view()
{
	// IF DATA FILE EXIST OR NOT.
	int d,p,q;
	char f[30],m[20],l[20],nn[20],ad[100],pno[20],mno[20],clear,confirm;
	char g,bco[20],jti[20],jdep[20];

	clrscr();
	dlscreen();

	lic = fopen("bookdata.abd","r");
	if(lic == NULL)
	{
		// DATA FILE DOES NOT EXIST.
		gotoxy(80/20,3);
		printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
		gotoxy(80/20,4);
		printf("--------------------------------------------------------------");
		gotoxy(80/20,5);
		printf(" No Data Found.");
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		mainmenu();
	}
	else
	{
		// DATA FILE EXIST.
		// SO, READ AND DISPLAY THE CONTENTS.
		gotoxy(3,3);
		printf("Press 'D' || 'd' To Clear Security Log File.");
		gotoxy(3,6);
		printf("Access|  First Name\n");
		p=3; q=7;
		while(feof(lic)==0)
		{
			fscanf(lic,"%d %s %s %s %s %s %s %s %c %s %s %s",&d,f,m,l,nn,ad,pno,mno,g,bco,jti,jdep);
			gotoxy(p,q);
			fprintf(stdout,"%6d|  %s\n",d,f);
			q=q+1;
		}
		fclose(lic); flushall();
		clear = getch();
		if(clear == 'D' || clear == 'd')
		{
			// CONFIRM USER WANT TO DELETE DATA FILE.
			gotoxy(3,3); printf("");
			gotoxy(3,3);
			printf("Are You Sure You Want To Clear Security Log File.");
			gotoxy(3,4);
			printf("Press 'Y|y' To Clear Or Any Key To Cancel: ");
			confirm = getch();
			if(confirm == 'y' || confirm == 'Y')
			{
				// USER HAS CONFIRM TO DELETE DATA FILE.
				if(remove("bookdata.abd")==0)
				{
					// REMOVE DATA FILE SUCCESSFUL.
					/* clear the screen */
					cleardevice();
					closegraph();
					mainmenu();
				}
				else
				{
					// REMOVE DATA FILE FAILED.
					clrscr();
					printf("System Error! Data Was Not Able To Clear");
					getch();
					/* clear the screen */
					cleardevice();
					closegraph();
					contactmenu();
				}
			}
			else
			{
				// USER HAS NOT CONFIRMED TO CLEAR DATA FILE.
				gotoxy(3,3);
				printf("Press 'D' || 'd' To Clear Security Log File.");
				gotoxy(3,4); printf("");
			}
		}
		else
		{
			// DONT CLEAR DATA FILES.
			// JUST MOVE TO MAIN MENU.
			/* clear the screen */
			cleardevice();
			closegraph();
			mainmenu();
		}
	}
}
// VIEW CONTACT MODULE ENDS.

// UPDATE SECURITY MODULE START.
void upsecurity()
{
	// UPDATE SECURITY.
	// CHECK OLD PASSWORD
	clrscr();
/**/    dlscreen();

	gotoxy(80/20,3);
	printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
	gotoxy(80/20,4);
	printf("--------------------------------------------------------------");
	gotoxy(80/20,5);
	printf(" [1] Password Must Be Between Min 4 And Max 8 Characters Long.");
	gotoxy(80/20,6);
	printf(" [2] Password Must Be Strong (Space Is Not Allowed).");
	gotoxy(80/20,7);
	printf(" [3] Space Is Not Allowed In Password If Did,");
	gotoxy(80/20,8);
	printf("     Rest After Space Will Be Ignored.");
	gotoxy(80/20,9);
	printf(" [4] You Can't See The Password, So Just Type It.");
	gotoxy(80/20,12);
	opass = getpass(" Enter Old Password : ");
	if(strlen(pass) == 0)
	{
		//INVALID PASSWORD.
		/* clear the screen */
		cleardevice();
		closegraph();
		err(2,6);
	}
	if(strlen(pass) < 4 || strlen(pass) > 8)
	{
		// INVALID PASSWORD.
		/* clear the screen */
		cleardevice();
		closegraph();
		err(2,5);
	}
	lic = fopen("ritybook.abp","r");
	fscanf(lic,"%s",oadmin);

	oc = strcmp(opass,oadmin);
	if(oc == 0)
	{
		// PASSWORD ARE EQUAL.
		// AUTHENTICATION SUCCESSFUL.
		// ENTER NEW PASSWORDS.
		gotoxy(80/20,14);
		pass = getpass(" Enter New Password : ");

		if(strlen(pass) == 0)
		{
			//INVALID PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,6);
		}
		if(strlen(pass) < 4 || strlen(pass) > 8)
		{
			// INVALID PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,5);
		}
		gotoxy(80/20,16);
		rpass = getpass(" Re-Enter Password  : ");

		if(strlen(rpass) == 0)
		{
			// INVALID REENTER PASSWORD.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,6);
		}
		if(strlen(rpass) < 4 || strlen(rpass) > 8)
		{
			// INVALID PASSWORD
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,5);
		}
		// CHECK PASSWORD AND CONFIRM PASSWORD MATCH.
		str = strcmp(pass,rpass);
		if(str == 0)
		{
			// PASSWORD MATCH.
			// SAVE THIS PASSWORD IN FILE.

			gotoxy(80/4,18);
			printf("Your Password Has Been Updated And Saved.");
			// INSTALL AND SAVED PASSWORD.
			lic = fopen("ritybook.abp","w");
			fprintf(lic,pass);
			fclose(lic); flushall();
			// INSTALL AND SAVE SECURITY FILE.
			// security = SECURITY HAS BEEN INSTALLED.
			// nosecurity = SECURITY IS NOT BEEN INSTALLED.
			lic = fopen("security.abs","w");
			fprintf(lic,"security");
			fclose(lic); flushall();
			getch();
			/* clear the screen */
			cleardevice();
			closegraph();
			mainmenu();
		}
		else
		{
			// PASSWORD MISMATCH.
			/* clear the screen */
			cleardevice();
			closegraph();
			err(2,4);
		}
	}
	else
	{
		// PASSWORD ARE NOT EQUAL.
		// AUTHENTICATION FAILED.
		/* clear the screen */
		cleardevice();
		closegraph();
		err(3,5);
	}
}
// UPDATE SECURITY MODULE ENDS.

// REMOVE SECURITY MODULE START.
void resecurity()
{
	// CHECK OLD PASSWORD IS SAME.
	// THEN REMOVE AND DELETE FILE
	// ELSE NOT AND SHOW ERROR.
	char re;
	clrscr();
/**/    dlscreen();

	gotoxy(80/20,3);
	printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
	gotoxy(80/20,4);
	printf("--------------------------------------------------------------");
	gotoxy(80/20,5);
	printf(" [1] Password Must Be Between Min 4 And Max 8 Characters Long.");
	gotoxy(80/20,6);
	printf(" [2] Password Must Be Strong (Space Is Not Allowed).");
	gotoxy(80/20,7);
	printf(" [3] Space Is Not Allowed In Password If Did,");
	gotoxy(80/20,8);
	printf("     Rest After Space Will Be Ignored.");
	gotoxy(80/20,9);
	printf(" [4] You Can't See The Password, So Just Type It.");
	gotoxy(80/20,12);
	opass = getpass(" Enter Old Password : ");
	if(strlen(pass) == 0)
	{
		//INVALID PASSWORD.
		/* clear the screen */
		cleardevice();
		closegraph();
		err(2,6);
	}
	if(strlen(pass) < 4 || strlen(pass) > 8)
	{
		// INVALID PASSWORD.
		/* clear the screen */
		cleardevice();
		closegraph();
		err(2,5);
	}
	lic = fopen("ritybook.abp","r");
	fscanf(lic,"%s",oadmin);

	oc = strcmp(opass,oadmin);
	if(oc == 0)
	{
		// PASSWORD ARE EQUAL.
		// AUTHENTICATION SUCCESSFUL.
		// REMOVE PASSWORD FILE.
		// UPDATE SECURITY FILE VALUE = NOSECURITY.
		fclose(lic); flushall();
		gotoxy(80/20,14);
		printf("  ARE YOU SURE YOU WANT TO REMOVE SECURITY SETTINGS!");
		gotoxy(80/20,15);
		printf("  PRESS `Y|y` TO REMOVE SECURITY / PRESS ANY KEY TO CANCEL ...");
		gotoxy(80/20,16);
		printf("  CONFIRMATION : ");
		re = getch();

		if(re == 'y' || re == 'Y')
		{
			// SURE TO REMOVE SECURITY.
			if(remove("ritybook.abp") == 0)
			{
				// PASSWORD FILE HAS BEEN REMOVED.
				gotoxy(80/20,18);
				printf("Your Security Has Been Removed");

				lic = fopen("security.abs","w");
				fprintf(lic,"noecurity");
				fclose(lic); flushall();
				getch();
				/* clear the screen */
				cleardevice();
				closegraph();
				mainmenu();
			}
			else
			{
				// PASSWORD FILE WAS NOT BE ABLE TO REMOVE.
				fclose(lic); flushall();
				clrscr();
				/**/
				/* initialize graphics and local variables */
				initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
				/* read result of initialization */
				errorcode = graphresult();
				if (errorcode != grOk)  /* an error occurred */
				{
					printf("Graphics error: %s\n", grapherrormsg(errorcode));
					printf("Press any key to halt:");
					getch();
					exit(1); /* terminate with an error code */
				}

				midx = getmaxx() / 2;
				midy = getmaxy() / 2;
				setcolor(getmaxcolor());
				/* for centering screen messages */
				settextjustify(CENTER_TEXT, CENTER_TEXT);

				/* output a message to the screen */
				outtextxy(midx, midy, "Security Error! : System Can't Able To Remove Security Settings.");
				/* wait for a key */
				getch();
				/* clear the screen */
				cleardevice();
				closegraph();
				getch();
				securitymenu();
			}
		}
		else
		{
			// NOT SURE TO EXIT.
			/* clear the screen */
			cleardevice();
			closegraph();
			securitymenu();
		}
	}
	else
	{
		// PASSWORD ARE NOT EQUAL.
		// AUTHENTICATION FAILED.
		clrscr();
		/* clear the screen */
		cleardevice();
		closegraph();
		err(3,5);
	}
}
// REMOVE SECURITY MODULE ENDS.

// INPUT DATA VALIDATION MODULE START.
void datavalidation(int iderr)
{
	// SET ERROR ENVIRONMENT.
	// 1 => BLANK SPACE.
	// 2 => ISDIGIT.
	// 3 => ISALPHA.
	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	setcolor(getmaxcolor());
	/* for centering screen messages */
	settextjustify(CENTER_TEXT, CENTER_TEXT);

	if(iderr == 1)
	{
		// SHOW ERROR FOR BLANK SPACE.
		/* output a message to the screen */
		outtextxy(midx, midy, "Input Error! : FIRST NAME IS REQUIRED FIELD.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}
	else if(iderr == 2)
	{
		// SHOW ERROR FOR INPUT DATA IS NOT IN DIGIT.
		/* output a message to the screen */
		outtextxy(midx, midy, "Input Error! : INVALID NUMBER.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}
	else if(iderr == 3)
	{
		// SHOW ERROR FOR INPUT DATA IS NOT IN ALPHABET.
		/* output a message to the screen */
		outtextxy(midx, midy, "Input Error! : INVALID ALPHABET.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}
	else if(iderr == 4)
	{
		// SHOW ERROR FOR INPUT DATA IS NOT IN ALPHABET.
		/* output a message to the screen */
		outtextxy(midx, midy, "Input Error! : Enter M/m For 'Male' OR F/f For 'Female'.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}
	else if(iderr == 5)
	{
		// SHOW ERROR FOR INPUT DATA IS NOT IN ALPHABET.
		/* output a message to the screen */
		outtextxy(midx, midy, "Input Error! : Invalid Contact No.");
		/* wait for a key */
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		add();
	}

}
// INPUT DATA VALIDATION MODULE ENDS.

// TRACE LOGIN SECURITY MODULE START.
void tracesecurityerror(int traceno)
{
	// 1 --> ACCESS DENIED.
	// 2 --> AUTHENTICATION FAILED.
	// GET THE DATA AND TIME OF SYSTEM
	// WHEN ANY END USER TRIED TO BREAK
	// INTO THE SYSTEM AND FAILED.
	getdate(&d);
	gettime(&t);
	switch(traceno)
	{
		case 1: // ACCESS DENIED.
			lic = fopen("trace.abi","a+");
			fprintf(lic,"%d %d %d",d.da_day,d.da_mon,d.da_year);
			fprintf(lic," %d %d %d %s\n",t.ti_hour,t.ti_min,t.ti_sec,"AccessDenied");
			fclose(lic); flushall();
		break;

		case 2: // AUTHENTICATION FAILED.
			lic = fopen("trace.abi","a+");
			fprintf(lic,"%d %d %d",d.da_day,d.da_mon,d.da_year);
			fprintf(lic," %d %d %d %s\n",t.ti_hour,t.ti_min,t.ti_sec,"AuthentucationFailed");
			fclose(lic); flushall();
		break;
	}
}
// TRACE LOGIN SECURITY MODULE ENDS.

// VIEW SECURITY LOG FILES MODULE START.
void logfile()
{
	// IF LOG FILE EXIST OR NOT.
	int d,mo,y,h,mi,s,p,q;
	long n;
	char v[30],clear,confirm;

	clrscr();
	dlscreen();

	lic = fopen("trace.abi","r");
	if(lic == NULL)
	{
		// LOG FILE DOES NOT EXIST.
		gotoxy(80/20,3);
		printf("WELCOME TO ADDRESS BOOK ++"); // GET USER NAME.
		gotoxy(80/20,4);
		printf("--------------------------------------------------------------");
		gotoxy(80/20,5);
		printf(" No Data Found.");
		getch();
		/* clear the screen */
		cleardevice();
		closegraph();
		mainmenu();
	}
	else
	{
		// LOG FILE EXIST.
		// SO, READ AND DISPLAY THE CONTENTS.
		gotoxy(3,3);
		printf("Press 'D' || 'd' To Clear Security Log File.");
		gotoxy(3,6);
		printf("Day|  Month|  Year|  Hour|  Minute|  Second|  Type \n");
		p=3; q=7;
		while(feof(lic)==0)
		{
			fscanf(lic,"%d %d %d %d %d %d %s",&d,&mo,&y,&h,&mi,&s,v);
			gotoxy(p,q);
			fprintf(stdout,"%3d|%7d|%6d|%6d|%8d|%8d|  %s\n",d,mo,y,h,mi,s,v);
			q=q+1;
		}
		fclose(lic); flushall();
		clear = getch();
		if(clear == 'D' || clear == 'd')
		{
			// CONFIRM USER WANT TO DELETE SECURITY LOG FILE.
			gotoxy(3,3); printf("");
			gotoxy(3,3);
			printf("Are You Sure You Want To Clear Security Log File.");
			gotoxy(3,4);
			printf("Press 'Y|y' To Clear Or Any Key To Cancel: ");
			confirm = getch();
			if(confirm == 'y' || confirm == 'Y')
			{
				// USER HAS CONFIRM TO DELETE SECURITY LOG FILE.
				if(remove("trace.abi")==0)
				{
					// REMOVE SECURITY LOG FILE SUCCESSFUL.
					/* clear the screen */
					cleardevice();
					closegraph();
					mainmenu();
				}
				else
				{
					// REMOVE SECURITY LOG FILE FAILED.
					clrscr();
					printf("System Error! Security Log Was Not Able To Clear");
					getch();
					/* clear the screen */
					cleardevice();
					closegraph();
					logfile();
				}
			}
			else
			{
				// USER HAS NOT CONFIRMED TO CLEAR LOG FILE.
				gotoxy(3,3);
				printf("Press 'D' || 'd' To Clear Security Log File.");
				gotoxy(3,4); printf("");
			}
		}
		else
		{
			// DONT CLEAR LOG FILES.
			// JUST MOVE TO MAIN MENU.
			/* clear the screen */
			cleardevice();
			closegraph();
			mainmenu();
		}
	}
}
// VIEW SECURITY LOG FILES MODULE ENDS.