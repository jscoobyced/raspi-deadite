void enableDisableChannel(unsigned char channel, unsigned char on_off);
void setAngle(unsigned char channel, unsigned int position, unsigned char speed);
unsigned int getPosition(unsigned char channel);
void initChannel(unsigned char channel, unsigned int position);
int startUart();
void closeUart();
