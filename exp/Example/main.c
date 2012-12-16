// main.c  -- simple serial communication test with Arduino --

#include "main.h"

#define SPEED B1152000
#define MAX_BUFLEN 100



int setupConnection(int fd)
{
    struct termios arduinoSettings;
    int ret = -1;
printf("Check point:  %d\n",  __LINE__ );
    ret = fcntl(fd, F_SETFL, 0);
    if (ret < 0)
        return(ret);
printf("Check point:  %d\n",  __LINE__ );
    // Read current settings for the serial port (fd) into variable "arduinoSettings"
    ret = tcgetattr(fd, &arduinoSettings);
    if (ret < 0)
        return(ret);
printf("Check point:  %d\n",  __LINE__ );
    // Set baud rates for serial input to 9600
    ret = cfsetispeed(&arduinoSettings, B9600);
    if (ret < 0)
        return(ret);
printf("Check point:  %d\n",  __LINE__ );
    // Set baud rates for serial output to 9600
    ret = cfsetospeed(&arduinoSettings, B9600);
    if (ret < 0)
        return(ret);
printf("Check point:  %d\n",  __LINE__ );
    // ------------- Control Options, set through c_cflag ----------------------

    // ignore status lines (such as carrier detect)
    arduinoSettings.c_cflag |= (CLOCAL | CREAD);
printf("Check point:  %d\n",  __LINE__ );
    // The Arduino uses the following (hard to change) settings for serial communication:
    // 8 data bits --  No parity -- 1 stop bit
    arduinoSettings.c_cflag &= ~CSIZE;
    arduinoSettings.c_cflag |= CS8;        // 8 data bits
    arduinoSettings.c_cflag &= ~PARENB;    // No parity bit
    arduinoSettings.c_cflag &= ~CSTOPB;    // 1 stop bit (complement of CSTOPB, otherwise 2 stop bits)
printf("Check point:  %d\n",  __LINE__ );
    // ------------- Local Options, set through c_lflag ----------------------
    // transfer of data line oriented \n indicates end of buffer
    arduinoSettings.c_lflag |= ICANON;
printf("Check point:  %d\n",  __LINE__ );
    arduinoSettings.c_lflag &= ~( ISIG | ECHO | ECHOE); // don't: enable signals, echo input
printf("Check point:  %d\n",  __LINE__ );
    // The settings for serial communication with Arduino will be realized through call to tcsetattr()
    // TCSANOW takes care of immediate change of settings; not wait for i/o that takes places at this moment
    ret = tcsetattr(fd, TCSANOW, &arduinoSettings);
printf("Check point:  %d\n",  __LINE__ );
    return (ret);
}




int main()
{
  printf("Check point:  %d\n",  __LINE__ );
    int fd, nRead, nWrite, loopCnt = 0;
    char inTxt[MAX_BUFLEN], outTxt[MAX_BUFLEN];
    printf("Check point:  %d\n",  __LINE__ );

    // try to open ttyUSB0, supposing this is your PC's USB-connection with your Arduino
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    printf("Check point:  %d\n",  __LINE__ );
    if (fd == -1)
    {
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
        return(-1);
    }
    printf("Check point:  %d\n",  __LINE__ );

    if (setupConnection(fd) == -1)
    {
        close(fd);
        perror("setupConnection(): Unable initialize serial port - ");
        return(-1);
    }
    printf("Check point:  %d\n",  __LINE__ );

    strcpy(outTxt, "Hello Arduino\n");
    nWrite = write(fd, outTxt, strlen(outTxt));
    printf("Check point:  %d\n",  __LINE__ );
    memset (inTxt, '\0', MAX_BUFLEN);
    printf("Check point:  %d\n",  __LINE__ );
    if (nWrite < 0)
    {
        close(fd);
        perror("1 - write: Unable to write to /dev/ttyUSB0 - ");
        return(-1);
    }
    printf("Check point:  %d\n",  __LINE__ );


    while (loopCnt <= LASTLOOP)
    {
      printf("Check point:  %d\n",  __LINE__ );
        nRead= read (fd, inTxt, MAX_BUFLEN-1);    // Read data from serial port (minus 1 for last 0-char)
        if(nRead == 0)
            continue;
printf("Check point:  %d\n",  __LINE__ );
        if(nRead < 0)
        {
            close(fd);
            perror("read: error reading from /dev/ttyUSB0 - ");
            return(-1);
        }
printf("Check point:  %d\n",  __LINE__ );
        printf("--- Text sent by Arduino: %s ---", inTxt); // it gets a '\n' from Arduino's Serial.println()
        memset (inTxt, '\0', MAX_BUFLEN);
printf("Check point:  %d\n",  __LINE__ );
        sprintf(outTxt,"loopCounter on PC = %d\n", ++loopCnt);
        nWrite = write(fd, outTxt, strlen(outTxt)); // write data to serial port
printf("Check point:  %d\n",  __LINE__ );
        if (nWrite < 0)
        {
            close(fd);
            perror("2 - write: Unable to write to /dev/ttyUSB0 - ");
            return(-1);
        }
printf("Check point:  %d\n",  __LINE__ );
    }

    close(fd);
    return(1);
}
