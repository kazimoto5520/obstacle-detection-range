#include <reg51.h>

// LCD Pins
sbit LCDrs = P2 ^ 0;
sbit LCDrw = P2 ^ 1;
sbit LCDen = P2 ^ 2;

// Ultrasonic Sensor Pins
sbit trig = P3 ^ 5;
sbit echo = P3 ^ 2;

// Alert Pins
sbit red_led   = P2 ^ 4;
sbit buzzer    = P2 ^ 5;
sbit green_led = P2 ^ 3;

void delay(unsigned int time);
void us_delay(void);
void command(unsigned char cmd);
void display_lcd(unsigned char location, unsigned char *d);
void get_range(void);

void main(void) {
    // Initialize LCD
    command(0x38); delay(1); // 2-line LCD
    command(0x0C); delay(1); // Display ON, Cursor OFF
    command(0x01); delay(2); // Clear display
    command(0x06); delay(1); // Entry mode

    display_lcd(0x80, "OBSTACLE IS AT");

    // Setup Timer0
    TMOD = 0x01;    // Timer0 mode 1 (16-bit)
    TH0 = 0x00;
    TL0 = 0x00;

    // Initialize output pins
    red_led = 0;
    green_led = 0;
    buzzer = 0;

    while (1) {
        get_range();
        delay(100); // update every 100 ms
    }
}

// Millisecond delay
void delay(unsigned int rtime) {
    unsigned int r, s;
    for (r = 0; r < rtime; r++)
        for (s = 0; s < 1275; s++);
}

// Microsecond delay for trigger pulse
void us_delay(void) {
    unsigned char i;
    for (i = 0; i < 10; i++);
}

// Send command to LCD
void command(unsigned char cmd) {
    LCDrs = 0;
    LCDrw = 0;
    P1 = cmd;
    LCDen = 1;
    delay(1);
    LCDen = 0;
}

// Display string to LCD
void display_lcd(unsigned char location, unsigned char *d) {
    command(location);
    delay(1);
    while (*d) {
        LCDrs = 1;
        LCDrw = 0;
        P1 = *d;
        LCDen = 1;
        delay(1);
        LCDen = 0;
        delay(1);
        d++;
    }
}

// Measure and display distance
void get_range(void) {
    unsigned int timerval = 0;
    unsigned int range = 0;
    char str[8] = "000cm ";
    int i = 2;

    // Trigger pulse (10us)
    trig = 1;
    us_delay();
    trig = 0;

    // Wait for echo HIGH
    while (echo == 0);
    TR0 = 1; // start timer

    // Wait for echo LOW
    while (echo == 1);
    TR0 = 0; // stop timer

    // Read timer count
    timerval = (TH0 << 8) | TL0;
    TH0 = 0; TL0 = 0; // clear timer

    // Calculate distance (approx. in cm)
    if (timerval < 34300)
        range = timerval / 58;
    else
        range = 0;

    // Format distance as string
    if (range > 0) {
        while (range && i >= 0) {
            str[i] = 0x30 | (range % 10);
            range = range / 10;
            i--;
        }
    } else {
        str[0] = '0'; str[1] = '0'; str[2] = '0';
    }

    // Display on LCD (2nd line)
    display_lcd(0xC0, "       ");  // clear line
    display_lcd(0xC0, str);        // print distance

    // LED + Buzzer logic
    range = timerval / 58;
    if (range > 0 && range < 100) {
        red_led = 1;
        green_led = 0;
        for (i = 0; i < 3; i++) {
        buzzer = 1;
        delay(50);       // ON for 50 ms
        buzzer = 0;
        delay(50);       // OFF for 50 ms
    }
    } else if (range >= 100 && range < 400) {
        red_led = 0;
        green_led = 1;
        buzzer = 0;
    } else {
        // out of range
        red_led = 0;
        green_led = 0;
        buzzer = 0;
    }
}