#include <genieArduino.h>
#include <protosmart.h>

/* Using all 16 analog pins
   using 3 digital pins
   */

void setup() 
{ 
    genieSetup(9600);

}

void loop() 
{ 
    genieWriteObj(GENIE_OBJ_FORM, 0, 0);

    while(1)
    {
        get_board_data();
        lcd_update();
        delay(50);
    }

}

void get_board_data()
{
    update_analog_values();

}

void lcd_update()
{
    /* 
       Frame descriptions:
       0 - 5 node values, selector for node numbers
       1 - graph for time varying signals
       2 - 
     */

	/* user_node_voltages is the current voltages of the selected nodes */
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 0, user_node_voltages[0]);
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 1, user_node_voltages[1]);
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 2, user_node_voltages[2]);
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 3, user_node_voltages[3]);

	/* number currently being punched in by the user */
	genieWriteObject(GENIE_OBJ_LED_DIGITS, 4, input_digit);
s 	
	/* user_node_indexes are selected nodes (numbers displayed) */
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 5, user_node_indexes[4]);
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 6, user_node_indexes[5]);
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 7, user_node_indexes[6]);
    genieWriteObject(GENIE_OBJ_LED_DIGITS, 8, user_node_indexes[7]);
 
 /*
    genieWriteObject(GENIE_OBJ_STRINGS, 0, user_request_nodes[0]);
    genieWriteObject(GENIE_OBJ_STRINGS, 1, user_request_nodes[1]);
    genieWriteObject(GENIE_OBJ_STRINGS, 2, user_request_nodes[2]);
    genieWriteObject(GENIE_OBJ_STRINGS, 3, user_request_nodes[3]);
	*/

    input_digit = genieReadObject(GENIE_OBJ_KEYBOARD, 0);

}

void update_analog_values()
{
}


//LONG HAND VERSION, MAYBE MORE VISIBLE AND MORE LIKE VERSION 1 OF THE LIBRARY
void myGenieEventHandler(void) 
{
  genieFrame Event;
  genieDequeueEvent(&Event);

  int slider_val = 0;

  //If the cmd received is from a Reported Event
  if(Event.reportObject.cmd == GENIE_REPORT_EVENT)
  {
    if (Event.reportObject.object == GENIE_OBJ_SLIDER)                // If the Reported Message was from a Slider
    {
      if (Event.reportObject.index == 0)                              // If Slider0
      {
        slider_val = (Event.reportObject.data_msb << 8) + Event.reportObject.data_lsb;  // Slider0 data into the slider_val setpoint  
        genieWriteObject(GENIE_OBJ_LED_DIGITS, 0x00, slider_val);     // Write Slider0 value to to LED Digits 0
      }
    }
  }

  //If the cmd received is from a Reported Object, which occurs if a Read Object is requested in the main code, reply processed here.
  if(Event.reportObject.cmd == GENIE_REPORT_OBJ)
  {
    if (Event.rportObject.object == GENIE_OBJ_SLIDER)                // If the Reported Message was from a Slider
    {
      if (Event.reportObject.index == 0)                              // If Slider0
      {
        slider_val = (Event.reportObject.data_msb << 8) + Event.reportObject.data_lsb;  // Slider0 data into the slider_val setpoint  
        genieWriteObject(GENIE_OBJ_LED_DIGITS, 0x00, slider_val);     // Write Slider0 value to to LED Digits 0
      }
    }
  }

  //This can be expanded as more objects are added that need to be captured

  //Event.reportObject.cmd is used to determine the command of that event, such as an reported event
  //Event.reportObject.object is used to determine the object type, such as a Slider
  //Event.reportObject.index is used to determine the index of the object, such as Slider0
  //Event.reportObject.data_msb and _lsb are used to save the data to a variable. They are in bytes, need to be combined to save as integer.
}

