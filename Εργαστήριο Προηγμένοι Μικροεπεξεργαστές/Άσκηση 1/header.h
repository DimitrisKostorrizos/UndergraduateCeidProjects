typedef volatile struct _PIO
{
	unsigned int PER;
	unsigned int PDR; 
	unsigned int PSR; 
	unsigned int Reserved0; 
	unsigned int OER; 
	unsigned int ODR; 
	unsigned int OSR; 
	unsigned int Reserved1; 
	unsigned int IFER; 
	unsigned int IFDR; 
	unsigned int IFSR; 
	unsigned int Reserved2;
	unsigned int SODR;
	unsigned int CODR;
	unsigned int ODSR;
	unsigned int PDSR;
	unsigned int IER;
	unsigned int IDR;
	unsigned int IMR;
	unsigned int ISR;
	unsigned int MDER;
	unsigned int MDDR;
	unsigned int MDSR;
	unsigned int Reserved3;
	unsigned int PUDR;
	unsigned int PUER;
	unsigned int PUSR;
	unsigned int Reserved4;
	unsigned int ASR;
	unsigned int BSR;
	unsigned int ABSR;
	unsigned int Reserved5[9];
	unsigned int OWER;
	unsigned int OWDR;
	unsigned int OWSR;
}PIO;

typedef volatile struct _AIC
{
	unsigned int SMR[32];
	unsigned int SVR[32];
	unsigned int IVR;
	unsigned int FVR;
	unsigned int ISR;
	unsigned int IPR;
	unsigned int IMR;
	unsigned int CISR;
	unsigned int Reserved1[2];
	unsigned int IECR;
	unsigned int IDCR;
	unsigned int ICCR;
	unsigned int ISCR;
	unsigned int EICR;
	unsigned int SPUR;
	unsigned int DCR;
	unsigned int Reserved2;
	unsigned int FFER;
	unsigned int FFDR;
	unsigned int FFSR;
}AIC;

typedef volatile struct _TCCHAN
{
	unsigned int CCR;
	unsigned int CMR;
	unsigned int Reserved1[2]; 
	unsigned int CV;
	unsigned int RA;
	unsigned int RB;
	unsigned int RC;
	unsigned int SR;
	unsigned int IER;
	unsigned int IDR;
	unsigned int IMR;
	unsigned int Reserved2[4];
}TCCHAN;

typedef volatile struct _TC
{
	TCCHAN Channel_0;
	TCCHAN Channel_1;
	TCCHAN Channel_2;
	unsigned int BCR;
	unsigned int BMR;
}TC;


#define STARTUP \
unsigned int _FIQtmp; \
int fd = open("/dev/mem", O_RDWR | O_SYNC); \
int fd2 = open("/proc/FIQ", O_RDWR | O_SYNC); \
char* mptr = mmap(0, 0x1000, PROT_READ | PROT_WRITE, \
MAP_SHARED, fd, 0xFFFFF000); \
char* pptr = mmap(0, 0x1000, PROT_READ | PROT_WRITE, \
MAP_SHARED, fd, 0xFFFA0000); \
if(mptr == MAP_FAILED || pptr == MAP_FAILED){ \
close(fd); \
close(fd2); \
exit(1); \
} \
pioa = (PIO*)(mptr + 0x400); \
aic = (AIC*)(mptr); \
tc = (TC*)(pptr); \
_FIQtmp = (unsigned int)FIQ_handler; \
write(fd2, &_FIQtmp, sizeof(unsigned int)); \
_FIQtmp = fcntl(STDIN_FILENO, F_GETFL, 0); \
_FIQtmp |= O_NONBLOCK; \
fcntl(STDIN_FILENO, F_SETFL, _FIQtmp)
#define CLEANUP \
_FIQtmp = fcntl(STDIN_FILENO, F_GETFL, 0); \
_FIQtmp &= O_NONBLOCK; \
fcntl(STDIN_FILENO, F_SETFL, _FIQtmp); \
munmap(mptr, 0x1000); \
munmap(pptr, 0x1000); \
close(fd); \
close(fd2)

#define DISABLE_FIQ \
{ \
unsigned int __Reg_save; \
asm("mrs %0, cpsr;" \
"orr %0, %0, #0x40;" \
"msr cpsr_c, %0;" \
:"=r" (__Reg_save) \
:"r"(__Reg_save) \
);}
#define ENABLE_FIQ \
{ \
unsigned int __Reg_save; \
asm("mrs %0, cpsr;" \
"bic %0, %0, #0x40;" \
"msr cpsr_c, %0;" \
:"=r" (__Reg_save) \
:"r"(__Reg_save) \
);}
