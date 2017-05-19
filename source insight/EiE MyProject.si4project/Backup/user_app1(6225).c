/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */
static u8 UserApp_au8MyName[] = "Xue YunFeng"; 
static u8 UserApp_CursorPosition;
/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
   //****************************************************
   LCDCommand(LCD_CLEAR_CMD);
   LCDMessage(LINE1_START_ADDR,UserApp_au8MyName);
   LCDMessage(LINE2_START_ADDR,"0");
   LCDMessage(LINE2_START_ADDR+6,"1");
   LCDMessage(LINE2_START_ADDR+13,"2");
   LCDMessage(LINE2_END_ADDR,"3");   
  //******************************************************
    LCDCommand(LCD_HOME_CMD);
    UserApp_CursorPosition = LINE1_START_ADDR;
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    //UserApp1_StateMachine = UserApp1SM_Idle;
    UserApp1_StateMachine = Debug_Interface;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
   /* Existing variables (defined in other files)      */
     extern u8 G_au8DebugScanfBuffer[];  /* From debug.c */
     extern u8 G_u8DebugScanfCharCount;  /* From debug.c */
     //DEBUG_SCANF_BUFFER_SIZE 
void Debug_Interface(void)
{
  u8 u8_a_name[]="xyf";
  u8 u8_namecounter=0;
  static u8 u8_a_tset[20];   //The array used for comparison
  u8 u8_namelength=strlen(u8_a_name);   //The length of the name
  static u8 u8_number='0';
  u8* number=&u8_number;
  bool test_result=TRUE;
  u8 u8_a_string1[]="*";  
  u16 u16_a_string2[]=u8_number;
  u16 u16_a_stinglength=4+sizeof(u16_a_string2)/sizeof(u16);

  
  if(G_u8DebugScanfCharCount >= u8_namelength)
  {
           for(u8 i=0;i<=G_u8DebugScanfCharCount;i++)
           {
             u8_a_tset[i]=G_au8DebugScanfBuffer[i];
           }
           for(u8 n=G_u8DebugScanfCharCount-u8_namelength;n<=G_u8DebugScanfCharCount-1;n++)
      	{       	  
          if(u8_a_tset[n]!=u8_a_name[u8_namecounter])
          	{
              test_result=FALSE;
		  }	 
	    u8_namecounter++;  
	  }
	  if(test_result==TRUE)
	  	{
		 u8_number++;
		 DebugLineFeed();
        for(u16 m=0;m<=u16_a_stinglength-1;m++)
	  	    {
            DebugPrintf(u8_a_string1);
		}
        DebugLineFeed();
        for(u16 x=0;x<=1;x++)
        	{
        	DebugPrintf(u8_a_string1);
        }
		DebugPrintf(number);
		for(u16 y=0;y<=1;y++)
	        {
			 DebugPrintf(u8_a_string1);
		}

		DebugLineFeed();
		for(u16 n=0;n<=u16_a_stinglength-1;n++)
	  	    {
            DebugPrintf(u8_a_string1);
		}
        DebugLineFeed();
		test_result=FALSE;
	  }
  }
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
void BCD_Code_display(void){
  
}
  /*eie way 
  static u16 u16BlinkCount = 0;
   static u8 u8Counter = 0,u8OverCounter=0;

  u16BlinkCount++;
  if(u16BlinkCount == 1000)
  {
    u16BlinkCount = 0;
    
    
    u8Counter++;
    if(u8Counter == 10)
    {
      u8Counter = 0;
      u8OverCounter++;
    }
    if(u8OverCounter==10)
      u8OverCounter=0;
  if(u8Counter & 0x01)
    {
      LedOn(RED);
    }
    else
    {
      LedOff(RED);
    }

    if(u8Counter & 0x02)
    {
      LedOn(ORANGE);
    }
    else
    {
      LedOff(ORANGE);
    }

    if(u8Counter & 0x04)
    {
      LedOn(YELLOW);
    }
    else
    {
      LedOff(YELLOW);
    }

    if(u8Counter & 0x08)
    {
      LedOn(GREEN);
    }
    else
    {
      LedOff(GREEN);
    }
    //1 9
    if(u8OverCounter& 0x01)
    {
      LedOn(CYAN);
    }
    else
    {
      LedOff(CYAN);
    }

    if(u8OverCounter& 0x02)
    {
      LedOn(BLUE);
    }
    else
    {
      LedOff(BLUE);
    }

    if(u8OverCounter & 0x04)
    {
      LedOn(PURPLE);
    }
    else
    {
      LedOff(PURPLE);
    }

    if(u8OverCounter & 0x08)
    {
      LedOn(WHITE);
    }
    else
    {
      LedOff(WHITE);
    }
  }
} 
   end eie way */ 

  /* teacher ways
  static u16 u16_counter = 0;
  static u8 a_u8_binary[8]= 0;
   u8 u8_temp_counter;
   u16 u16_counter1 = 0;
   u16 u16_counter2 = 0;
   if(G_u32SystemTime1ms%1000==0)
   {
    u16_counter++;
     if(u16_counter==99)
       u16_counter=0;
   }
   u16_counter1=u16_counter%10;
  for(u8_temp_counter = 7;u8_temp_counter>=4&&u8_temp_counter <=7;u8_temp_counter--)
   {
     a_u8_binary[u8_temp_counter]=u16_counter1%2;
             u16_counter1=u16_counter1/2;
   }
   u16_counter2=u16_counter/10;
   for(u8_temp_counter = 3;u8_temp_counter>=0&&u8_temp_counter <=3;u8_temp_counter--)
   {
     a_u8_binary[u8_temp_counter]=u16_counter2%2;
             u16_counter2=u16_counter2/2;
   }
   for(u8_temp_counter = 0;u8_temp_counter <=7;u8_temp_counter++)
   {
     if(a_u8_binary[u8_temp_counter]==1)
       LedOn(u8_temp_counter);
   else
       LedOff(u8_temp_counter);
   }
}   end teacher way*/
  
 /*  my way
  static u16 u16_Counter=0;
  static u8 u8_Led_Number=0;
  static u16 u16_unit=0;
  static u16 u16_decade=0;
  if(G_u32SystemTime1ms==1000){
     u16_Counter++;
     if(u16_Counter>=99){
        u16_Counter=0;       
     } 
     u16_unit=u16_Counter%10;
     u16_decade=u16_Counter/10;
     for(u8_Led_Number=7;u8_Led_Number>=4;u8_Led_Number--){
       if(u16_unit%2==0){
          LedOff(u8_Led_Number);
       }
       else{
          LedOn(u8_Led_Number);
       }
       u16_unit=u16_unit/2;
     }
     for(u8_Led_Number=3;u8_Led_Number>=0;u8_Led_Number--){
       if(u16_decade%2==0){
          LedOff(u8_Led_Number);
       }
       else{
          LedOn(u8_Led_Number);
       }
       u16_decade=u16_decade/2;
     }    
  }
}
 end my way*/
 
 /*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static bool bCursorOn = FALSE;
  
  if(WasButtonPressed(BUTTON0))
  {
    ButtonAcknowledge(BUTTON0);
    
    if(bCursorOn)
    {
      /* Cursor is on, so turn it off */
      LCDCommand(LCD_DISPLAY_CMD | LCD_DISPLAY_ON);
      bCursorOn = FALSE;
    }
    else
    {
      /* Cursor is off, so turn it on */
      LCDCommand(LCD_DISPLAY_CMD | LCD_DISPLAY_ON | LCD_DISPLAY_CURSOR | LCD_DISPLAY_BLINK);
      bCursorOn = TRUE;
   }
  }
   /* BUTTON3 moves the cursor forward one position */
  if(WasButtonPressed(BUTTON3))
  {
    ButtonAcknowledge(BUTTON3);
    
    /* Handle the two special cases or just the regular case */
    if(UserApp_CursorPosition == LINE1_END_ADDR)
    {
      UserApp_CursorPosition = LINE2_START_ADDR;
    }

    else if (UserApp_CursorPosition == LINE2_END_ADDR)
    {
      UserApp_CursorPosition = LINE1_START_ADDR;
    }
    
    /* Otherwise just increment one space */
    else
    {
      UserApp_CursorPosition++;
    }
    
    /* New position is set, so update */
    LCDCommand(LCD_ADDRESS_CMD | UserApp_CursorPosition);
  } /* end BUTTON3 */ 
} /* end UserApp1SM_Idle() */
    
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
