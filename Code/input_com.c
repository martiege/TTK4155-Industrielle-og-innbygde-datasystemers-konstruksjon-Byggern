#include "input_com.h"

#ifdef __AVR_ATmega162__
    #include "user_input.h"
#endif

/*Evt putte Position etc i egen fil for å gjenbruke her, senere*/

void put_message()
{
    /*
    message.data[0]     = user_data.pos.X;
    message.data[1]     = user_data.pos.Y;
    message.data[2]     = user_data.sli.left;
    message.data[3]     = user_data.sli.right;
    message.data[4]     = user_data.but;
    */

    input_message.data[0]     = (uint8_t)user_data.pos_X;
    input_message.data[1]     = (uint8_t)user_data.pos_Y;
    input_message.data[2]     = user_data.sli_left;
    input_message.data[3]     = user_data.sli_right;
    input_message.data[4]     = user_data.but;

}

void get_message()
{
    /*
    user_data.pos.X     = message.data[0];
    user_data.pos.Y     = message.data[1];
    user_data.sli.left  = message.data[2];
    user_data.sli.right = message.data[3];
    user_data.but       = message.data[4];
    */

    user_data.pos_X     = (int8_t)input_message.data[0];
    user_data.pos_Y     = (int8_t)input_message.data[1];
    user_data.sli_left  = input_message.data[2];
    user_data.sli_right = input_message.data[3];
    user_data.but       = input_message.data[4];
}



#ifdef __AVR_ATmega162__
void update_user_data()
{
    /*
    user_data.pos = user_input_joystick_position();
    user_data.sli = user_input_slider_position();
    user_data.but = user_input_joystick_button();
    */

    Position p = user_input_joystick_position();
    Slider s = user_input_slider_position();

    user_data.pos_X     = p.X;
    user_data.pos_Y     = p.Y;
    user_data.sli_left  = s.left;
    user_data.sli_right = s.right;
    user_data.but       = user_input_joystick_button();
}
#endif

void input_com_init()
{
    input_message.id = INPUT_COM;
    input_message.length = 5;
    for (int i = 0; i < 8; ++i)
    {
        input_message.data[i] = 0;
    }

    user_data.pos_X     = 0;
    user_data.pos_Y     = 0;
    user_data.sli_left  = 0;
    user_data.sli_right = 0;
    user_data.but       = 0;
}

#ifdef __AVR_ATmega162__
USER_DATA input_com_send()
{
    //message.id = INPUT_COM;
    //message.length = 5;
    
    update_user_data();
    put_message();

    CAN_send(&input_message);

    return user_data;
}
#endif

USER_DATA input_com_recieve()
{
    CAN_receive(&input_message);
    get_message();

    return user_data;
}

