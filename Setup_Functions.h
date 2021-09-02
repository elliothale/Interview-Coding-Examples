void Get_Values(void){
    int cursor_row = 1;
    int cursor_col = 20;
    LCD_command(DISP_CL);
    __delay_ms(2);
    LCD_xy(1,1);
    LCD_string("Cycles    =   000000");
    LCD_xy(1,2);
    LCD_string("UP(sec)   =      000");
    LCD_xy(1,3);
    LCD_string("DOWN(sec) =      000");
    LCD_xy(1,4);
    LCD_string("REST(min) =      000");
    LCD_xy(cursor_col,cursor_row);
    LCD_command(0x0f);
    __delay_ms(2);
    cursor_col = 1;
    cursor_row = 1;
    while(OK == 0)
    {
        if((UP_BUTTON == 1) && (cursor_row > 1))
        {
            cursor_row--;
            LCD_xy(20,cursor_row);
            cursor_col = 1;
            __delay_ms(2);
            while(UP_BUTTON == 1)
            {
                __delay_ms(25);
            }
        }
        else if((DOWN_BUTTON == 1) && (cursor_row < 4))
        {
            cursor_row++;
            LCD_xy(20,cursor_row);
            cursor_col = 1;
            __delay_ms(2);
            while(DOWN_BUTTON == 1)
            {
                __delay_ms(25);
            }
        }
        switch(cursor_row)
        {
            
            case(1):    if((LEFT == 1) && (cursor_col < 6))
                        {
                            cursor_col++;
                            LCD_command(0x10);
                            __delay_ms(2);
                            while(LEFT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        else if((RIGHT == 1) && (cursor_col > 1))
                        {
                            cursor_col--;
                            LCD_command(0x14);
                            __delay_ms(2);
                            while(RIGHT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        if(INCREMENT == 1)
                        {
                            switch(cursor_col)
                            {
                                case 1: Cycle_bits[0]++;
                                        if(Cycle_bits[0] > 9){Cycle_bits[0] = 0;}
                                        break;
                                case 2: Cycle_bits[1]++;
                                        if(Cycle_bits[1] > 9){Cycle_bits[1] = 0;}
                                        break;
                                case 3: Cycle_bits[2]++;
                                        if(Cycle_bits[2] > 9){Cycle_bits[2] = 0;}
                                        break;
                                case 4: Cycle_bits[3]++;
                                        if(Cycle_bits[3] > 9){Cycle_bits[3] = 0;}
                                        break;
                                case 5: Cycle_bits[4]++;
                                        if(Cycle_bits[4] > 9){Cycle_bits[4] = 0;}
                                        break;
                                case 6: Cycle_bits[5]++;
                                        if(Cycle_bits[5] > 9){Cycle_bits[5] = 0;}
                                        break;
                                default: break;              
                            }
                            sprintf(value,"Cycles    =   %d%d%d%d%d%d",Cycle_bits[5],Cycle_bits[4],Cycle_bits[3],Cycle_bits[2],Cycle_bits[1],Cycle_bits[0]);
                            LCD_xy(1,1);
                            __delay_ms(2);
                            LCD_string(value);
                            __delay_ms(2);
                            LCD_xy(20+1-cursor_col,1);
                            while(INCREMENT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        break;
                        
            case(2):    if((LEFT == 1) && (cursor_col < 3))
                        {
                            cursor_col++;
                            LCD_command(0x10);
                            __delay_ms(2);
                            while(LEFT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        else if((RIGHT == 1) && (cursor_col > 1))
                        {
                            cursor_col--;
                            LCD_command(0x14);
                            __delay_ms(2);
                            while(RIGHT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        if(INCREMENT == 1)
                        {
                        switch(cursor_col)
                            {
                            case 1: UP_bits[0]++;
                                    if(UP_bits[0] > 9){UP_bits[0] = 0;}
                                    break;
                            case 2: UP_bits[1]++;
                                    if(UP_bits[1] > 9){UP_bits[1] = 0;}
                                    break;
                            case 3: UP_bits[2]++;
                                    if(UP_bits[2] > 9){UP_bits[2] = 0;}
                                    break;
                            default: break;              
                            }
                        sprintf(value,"UP(sec)   =      %d%d%d",UP_bits[2],UP_bits[1],UP_bits[0]);
                        LCD_xy(1,2);
                        __delay_ms(2);
                        LCD_string(value);
                        __delay_ms(2);
                        LCD_xy(20+1-cursor_col,2);
                        while(INCREMENT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        break;
                        
            case(3):    if((LEFT == 1) && (cursor_col < 3))
                        {
                            cursor_col++;
                            LCD_command(0x10);
                            __delay_ms(2);
                            while(LEFT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        else if((RIGHT == 1) && (cursor_col > 1))
                        {
                            cursor_col--;
                            LCD_command(0x14);
                            __delay_ms(2);
                            while(RIGHT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        if(INCREMENT == 1)
                        {
                            switch(cursor_col)
                            {
                                case 1: DOWN_bits[0]++;
                                        if(DOWN_bits[0] > 9){DOWN_bits[0] = 0;}
                                        break;
                                case 2: DOWN_bits[1]++;
                                        if(DOWN_bits[1] > 9){DOWN_bits[1] = 0;}
                                        break;
                                case 3: DOWN_bits[2]++;
                                        if(DOWN_bits[2] > 9){DOWN_bits[2] = 0;}
                                        break;
                                default: break;              
                            }
                            sprintf(value,"DOWN(sec) =      %d%d%d",DOWN_bits[2],DOWN_bits[1],DOWN_bits[0]);
                            LCD_xy(1,3);
                            __delay_ms(2);
                            LCD_string(value);
                            __delay_ms(2);
                            LCD_xy(20+1-cursor_col,3);
                            while(INCREMENT == 1)
                                {
                                    __delay_ms(25);
                                }
                        }
                        break;
                        
            case(4):    if((LEFT == 1) && (cursor_col < 3))
                        {
                            cursor_col++;
                            LCD_command(0x10);
                            __delay_ms(2);
                            while(LEFT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        else if((RIGHT == 1) && (cursor_col > 1))
                        {
                            cursor_col--;
                            LCD_command(0x14);
                            __delay_ms(2);
                            while(RIGHT == 1)
                            {
                                __delay_ms(25);
                            }
                        }
                        if(INCREMENT == 1)
                        {
                            switch(cursor_col)
                            {
                                case 1: REST_bits[0]++;
                                        if(REST_bits[0] > 9){REST_bits[0] = 0;}
                                        break;
                                case 2: REST_bits[1]++;
                                        if(REST_bits[1] > 9){REST_bits[1] = 0;}
                                        break;
                                case 3: REST_bits[2]++;
                                        if(REST_bits[2] > 9){REST_bits[2] = 0;}
                                        break;
                                default: break;              
                            }
                            sprintf(value,"REST(min) =      %d%d%d",REST_bits[2],REST_bits[1],REST_bits[0]);
                            LCD_xy(1,4);
                            __delay_ms(2);
                            LCD_string(value);
                            __delay_ms(2);
                            LCD_xy(20+1-cursor_col,4);
                            while(INCREMENT == 1)
                                {
                                    __delay_ms(25);
                                }
                        }
                        break;
                        
            default:    break;
        }
    }
    Cycles = Cycle_bits[0] + (Cycle_bits[1] * 10) + (Cycle_bits[2] * 100) + (Cycle_bits[3] * 1000) + (Cycle_bits[4] * 10000) + (Cycle_bits[5] * 100000);
    UP_time = UP_bits[0] + (UP_bits[1] * 10) + (UP_bits[2] * 100);
    DOWN_time = DOWN_bits[0] + (DOWN_bits[1] * 10) + (DOWN_bits[2] * 100);
    REST_time = REST_bits[0] + (REST_bits[1] * 10) + (REST_bits[2] * 100);
    while(OK == 1){__delay_ms(25);}
}

void Confirm_Settings(void)
{
    LCD_command(DISP_CL);
    __delay_ms(2);
    if(FP_ON == true)
    {
        sprintf(value,"%ld Cycles, FP ON",Cycles);
    }
    else if(FP_ON == false)
    {
        sprintf(value,"%ld Cycles,FP OFF",Cycles);
    }
    LCD_xy(1,1);
    LCD_string(value);
    sprintf(value,"%ds Up, %ds Down",UP_time,DOWN_time);
    LCD_xy(1,2);
    LCD_string(value);
    sprintf(value,"%d min Rest",REST_time);
    LCD_xy(1,3);
    LCD_string(value);
    LCD_xy(1,4);
    LCD_string("Press OK to begin");
    __delay_ms(500);
    while(OK == 0)
    {
        __builtin_nop();
    }
}

/*
void Get_Cycles(void){
    LCD_command(DISP_CL);
    __delay_ms(2);
    Cursor_Position = 1;
    LCD_xy(1,1);
    LCD_string("How Many Cycles?");
    LCD_xy(1,2);
    LCD_string("Cycles =  000000");
    LCD_command(0x0f);
    __delay_ms(2);
    LCD_command(0x10);
    __delay_ms(2);
    while(OK == 0){
        if((LEFT == 1) && (Cursor_Position < 6)){
            Cursor_Position++;
            LCD_command(0x10);
            __delay_ms(2);
            while(LEFT == 1){
                __delay_ms(25);
            }
        }
        else if((RIGHT == 1) && (Cursor_Position > 1)){
            Cursor_Position--;
            LCD_command(0x14);
            __delay_ms(2);
            while(RIGHT == 1){
                __delay_ms(25);
            }
        }
        if(INCREMENT == 1){
            switch(Cursor_Position){
                case 1: Cycle_bits[0]++;
                        if(Cycle_bits[0] > 9){Cycle_bits[0] = 0;}
                        break;
                case 2: Cycle_bits[1]++;
                        if(Cycle_bits[1] > 9){Cycle_bits[1] = 0;}
                        break;
                case 3: Cycle_bits[2]++;
                        if(Cycle_bits[2] > 9){Cycle_bits[2] = 0;}
                        break;
                case 4: Cycle_bits[3]++;
                        if(Cycle_bits[3] > 9){Cycle_bits[3] = 0;}
                        break;
                case 5: Cycle_bits[4]++;
                        if(Cycle_bits[4] > 9){Cycle_bits[4] = 0;}
                        break;
                case 6: Cycle_bits[5]++;
                        if(Cycle_bits[5] > 9){Cycle_bits[5] = 0;}
                        break;
                default: break;              
            }
            sprintf(value,"Cycles =  %d%d%d%d%d%d",Cycle_bits[5],Cycle_bits[4],Cycle_bits[3],Cycle_bits[2],Cycle_bits[1],Cycle_bits[0]);
            LCD_xy(1,2);
            __delay_ms(2);
            LCD_string(value);
            __delay_ms(2);
            switch(Cursor_Position){
                case 1: LCD_command(0x10);__delay_ms(2);
                        break;
                case 2: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 3: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 4: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);    
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 5: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 6: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                default: break;              
            }
        }   
        while(INCREMENT == 1){
            __delay_ms(25);
        }
    }
    Cycles = Cycle_bits[0] + (Cycle_bits[1] * 10) + (Cycle_bits[2] * 100) + (Cycle_bits[3] * 1000) + (Cycle_bits[4] * 10000) + (Cycle_bits[5] * 100000);
    while(OK == 1){__delay_ms(25);}
}

void Get_UP_time(void){
    LCD_command(DISP_CL);
    __delay_ms(2);
    Cursor_Position = 1;
    LCD_xy(1,1);
    LCD_string("UP time(sec)?");
    LCD_xy(1,2);
    LCD_string("UP time =    000");
    LCD_command(0x0f);
    __delay_ms(2);
    LCD_command(0x10);
    __delay_ms(2);
    while(OK == 0){
        if((LEFT == 1) && (Cursor_Position < 3)){
            Cursor_Position++;
            LCD_command(0x10);
            __delay_ms(2);
            while(LEFT == 1){
                __delay_ms(25);
            }
        }
        else if((RIGHT == 1) && (Cursor_Position > 1)){
            Cursor_Position--;
            LCD_command(0x14);
            __delay_ms(2);
            while(RIGHT == 1){
                __delay_ms(25);
            }
        }
        if(INCREMENT == 1){
            switch(Cursor_Position){
                case 1: UP_bits[0]++;
                        if(UP_bits[0] > 9){UP_bits[0] = 0;}
                        break;
                case 2: UP_bits[1]++;
                        if(UP_bits[1] > 9){UP_bits[1] = 0;}
                        break;
                case 3: UP_bits[2]++;
                        if(UP_bits[2] > 9){UP_bits[2] = 0;}
                        break;
                default: break;              
            }
            sprintf(value,"UP time =    %d%d%d",UP_bits[2],UP_bits[1],UP_bits[0]);
            LCD_xy(1,2);
            __delay_ms(2);
            LCD_string(value);
            __delay_ms(2);
            switch(Cursor_Position){
                case 1: LCD_command(0x10);__delay_ms(2);
                        break;
                case 2: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 3: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                default: break;              
            }
            while(INCREMENT == 1){
                __delay_ms(25);
            }
        }
    }
    UP_time = UP_bits[0] + (UP_bits[1] * 10) + (UP_bits[2] * 100);
    while(OK == 1){__delay_ms(25);}
}

void Get_DOWN_time(void){
    LCD_command(DISP_CL);
    __delay_ms(2);
    Cursor_Position = 1;
    LCD_xy(1,1);
    LCD_string("DOWN time(sec)?");
    LCD_xy(1,2);
    LCD_string("DOWN time =  000");
    LCD_command(0x0f);
    __delay_ms(2);
    LCD_command(0x10);
    __delay_ms(2);
    while(OK == 0){
        if((LEFT == 1) && (Cursor_Position < 3)){
            Cursor_Position++;
            LCD_command(0x10);
            __delay_ms(2);
            while(LEFT == 1){
                __delay_ms(25);
            }
        }
        else if((RIGHT == 1) && (Cursor_Position > 1)){
            Cursor_Position--;
            LCD_command(0x14);
            __delay_ms(2);
            while(RIGHT == 1){
                __delay_ms(25);
            }
        }
        if(INCREMENT == 1){
            switch(Cursor_Position){
                case 1: DOWN_bits[0]++;
                        if(DOWN_bits[0] > 9){DOWN_bits[0] = 0;}
                        break;
                case 2: DOWN_bits[1]++;
                        if(DOWN_bits[1] > 9){DOWN_bits[1] = 0;}
                        break;
                case 3: DOWN_bits[2]++;
                        if(DOWN_bits[2] > 9){DOWN_bits[2] = 0;}
                        break;
                default: break;              
            }
            sprintf(value,"DOWN time =  %d%d%d",DOWN_bits[2],DOWN_bits[1],DOWN_bits[0]);
            LCD_xy(1,2);
            __delay_ms(2);
            LCD_string(value);
            __delay_ms(2);
            switch(Cursor_Position){
                case 1: LCD_command(0x10);__delay_ms(2);
                        break;
                case 2: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 3: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                default: break;              
            }
            while(INCREMENT == 1){
                __delay_ms(25);
            }
        }
    }
    DOWN_time = DOWN_bits[0] + (DOWN_bits[1] * 10) + (DOWN_bits[2] * 100);
    while(OK == 1){__delay_ms(25);}
}

void Get_REST_time(void){
    LCD_command(DISP_CL);
    __delay_ms(2);
    Cursor_Position = 1;
    LCD_xy(1,1);
    LCD_string("REST time(sec)?");
    LCD_xy(1,2);
    LCD_string("REST time =  000");
    LCD_command(0x0f);
    __delay_ms(2);
    LCD_command(0x10);
    __delay_ms(2);
    while(OK == 0){
        if((LEFT == 1) && (Cursor_Position < 3)){
            Cursor_Position++;
            LCD_command(0x10);
            __delay_ms(2);
            while(LEFT == 1){
                __delay_ms(25);
            }
        }
        else if((RIGHT == 1) && (Cursor_Position > 1)){
            Cursor_Position--;
            LCD_command(0x14);
            __delay_ms(2);
            while(RIGHT == 1){
                __delay_ms(25);
            }
        }
        if(INCREMENT == 1){
            switch(Cursor_Position){
                case 1: REST_bits[0]++;
                        if(REST_bits[0] > 9){REST_bits[0] = 0;}
                        break;
                case 2: REST_bits[1]++;
                        if(REST_bits[1] > 9){REST_bits[1] = 0;}
                        break;
                case 3: REST_bits[2]++;
                        if(REST_bits[2] > 9){REST_bits[2] = 0;}
                        break;
                default: break;              
            }
            sprintf(value,"REST time =  %d%d%d",REST_bits[2],REST_bits[1],REST_bits[0]);
            LCD_xy(1,2);
            __delay_ms(2);
            LCD_string(value);
            __delay_ms(2);
            switch(Cursor_Position){
                case 1: LCD_command(0x10);__delay_ms(2);
                        break;
                case 2: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                case 3: LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        LCD_command(0x10);__delay_ms(2);
                        break;
                default: break;              
            }
            while(INCREMENT == 1){
                __delay_ms(25);
            }
        }
    }
    REST_time = REST_bits[0] + (REST_bits[1] * 10) + (REST_bits[2] * 100);
    while(OK == 1){__delay_ms(25);}
}
*/
void Get_Footplate(void){
    LCD_command(0x0c);
    __delay_ms(2);
    LCD_command(DISP_CL);
    __delay_ms(2);
    LCD_xy(1,1);
    LCD_string("Automatic Footplate?");
    FP_ON = true;
    LCD_xy(1,2);
    LCD_string("YES<          NO");
    while(OK==0){
        if(RIGHT == 1)
        {
            FP_ON = false;
            LCD_xy(1,2);
            LCD_string("YES          >NO");
        }
        else if(LEFT == 1)
        {
            FP_ON = true;
            LCD_xy(1,2);
            LCD_string("YES<          NO");
        }
        while((LEFT == 1) || (RIGHT == 1))
        {
            __delay_ms(25);
        }
    }
    while(OK == 1){__delay_ms(25);}
}
