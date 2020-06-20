typedef volatile struct _PIO
{
	unsigned int PER; /** PIO Enable r e g i s t e r ( Wr i te−only ) */
	unsigned int PDR; /** PIO Di sabl e r e g i s t e r ( Wr i te−only ) */
	unsigned int PSR; /** PIO Status r e g i s t e r ( Read−only ) */
	unsigned int Reserved0; /** Unused r e g i s t e r */
	unsigned int OER; /** Output Enable r e g i s t e r ( Wr i te−only ) */
	unsigned int ODR; /** Output Di sabl e r e g i s t e r ( Wr i te−only ) */
	unsigned int OSR; /** Output Status r e g i s t e r ( Read−only ) */
	unsigned int Reserved1; /** Unused r e g i s t e r */
	unsigned int IFER; /** Gl i t c h Input f i l t e r Enable ( Wr i te−only ) */
	unsigned int IFDR; /** Gl i t c h Input f i l t e r Di sabl e ( Wr i te−only ) */
	unsigned int IFSR; /** Gl i t c h Input f i l t e r Status ( Read−only ) */
	unsigned int Reserved2; /** Unused r e g i s t e r */
	unsigned int SODR; /** Set Output Data r e g i s t e r ( Wr i te−only ) */
	unsigned int CODR; /** Cl ear Output Data r e g i s t e r ( Wr i te−only ) */
	unsigned int ODSR; /** Output Data Status r e g i s t e r ( Read−only ) */
	unsigned int PDSR; /** Pin Data Status r e g i s t e r ( Read−only ) */
	unsigned int IER; /** I n t e r r u p t Enable r e g i s t e r ( Wr i te−only ) */
	unsigned int IDR; /** I n t e r r u p t Di sabl e r e g i s t e r ( Wr i te−only ) */
	unsigned int IMR; /** I n t e r r u p t Mask r e g i s t e r ( Wr i te−only ) */
	unsigned int ISR; /** I n t e r r u p t Status r e g i s t e r ( Read−only ) */
	unsigned int MDER; /** Mul t i−d r i v e r Enable ( Wr i te−only ) */
	unsigned int MDDR; /** Mul t i−d r i v e r Di sabl e ( Wr i te−only ) */
	unsigned int MDSR; /** Mul t i−d r i v e r Status ( Read−only ) */
	unsigned int Reserved3; /** Unused r e g i s t e r */
	unsigned int PUDR; /** Pul l−up Di sabl e r e g i s t e r ( Wr i te−only ) */
	unsigned int PUER; /** Pul l−up Enable r e g i s t e r ( Wr i te−only ) */
	unsigned int PUSR; /** Pul l−up Status r e g i s t e r ( Read−only ) */
	unsigned int Reserved4; /** Unused r e g i s t e r */
	unsigned int ASR; /** P e r i p h e r a l A s e l e c t ( Wr i te−only ) */
	unsigned int BSR; /** P e r i p h e r a l B s e l e c t ( Wr i te−only ) */
	unsigned int ABSR; /** P e r i p h e r a l AB Status ( Read−only ) */
	unsigned int Reserved5[9]; /** Unused r e g i s t e r */
	unsigned int OWER; /** Output wr i t e enable ( Wr i te−only ) */
	unsigned int OWDR; /** Output wr i t e di sabl e ( Wr i te−only ) */
	unsigned int OWSR; /** Output wr i t e Status ( Read−only ) */
}PIO;

typedef volatile struct _AIC
{
	unsigned int SMR[32]; /** Source mode r e g i s t e r ( Read−Wr i t e ) */
	unsigned int SVR[32]; /** Source v e c t o r r e g i s t e r ( Read−Wr i t e ) */
	unsigned int IVR; /** I n t e r r u p t v e c t o r r e g i s t e r ( Read−only ) */
	unsigned int FVR; /** Fast I n t e r r u p t v e c t o r r e g i s t e r ( Read−only ) */
	unsigned int ISR; /** I n t e r r u p t s tatus r e g i s t e r ( Read−only ) */
	unsigned int IPR; /** I n t e r r u p t pending r e g i s t e r ( Read−only ) */
	unsigned int IMR; /** I n t e r r u p t mask r e g i s t e r ( Read−only ) */
	unsigned int CISR; /** Core I n t e r r u p t s tatus r e g i s t e r ( Read−only ) */
	unsigned int Reserved1[2]; /** Unused r e g i s t e r */
	unsigned int IECR; /** I n t e r r u p t enable command r e g i s t e r ( Wr i te−only ) */
	unsigned int IDCR; /** I n t e r r u p t di sabl e command r e g i s t e r ( Wr i te−only ) */
	unsigned int ICCR; /** I n t e r r u p t c l e a r command r e g i s t e r ( Wr i te−only ) */
	unsigned int ISCR; /** I n t e r r u p t s e t command r e g i s t e r ( Wr i te−only ) */
	unsigned int EICR; /** End o f I n t e r r u p t command r e g i s t e r ( Wr i te−only ) */
	unsigned int SPUR; /** Spur ious I n t e r r u p t v e c t o r r e g i s t e r ( Read−Wr i t e ) */
	unsigned int DCR; /** Debug c o n t r o l r e g i s t e r ( Read−Wr i t e ) */
	unsigned int Reserved2; /** Unused r e g i s t e r */
	unsigned int FFER; /** Fast Fo r c ing enable r e g i s t e r ( Wr i te−only ) */
	unsigned int FFDR; /** Fast Fo r c ing di sabl e r e g i s t e r ( Wr i te−only ) */
	unsigned int FFSR; /** Fast Fo r c ing s tatus r e g i s t e r ( Wr i te−only ) */
}AIC;

typedef volatile struct _TCCHAN
{
	unsigned int CCR; /** Channel Cont r o l Re g i s t e r ( Wr i te−only ) */
	unsigned int CMR; /** Channel Mode Re g i s t e r ( Read−Wr i t e ) */
	unsigned int Reserved1[2]; /** Unused r e g i s t e r */
	unsigned int CV; /** Counter Value ( Read−only ) */
	unsigned int RA; /** Re g i s t e r A ( Read−Wr i t e ) */
	unsigned int RB; /** Re g i s t e r B ( Read−Wr i t e ) */
	unsigned int RC; /** Re g i s t e r C ( Read−Wr i t e ) */
	unsigned int SR; /** Status Re g i s t e r ( Read−only ) */
	unsigned int IER; /** I n t e r r u p t Enable Re g i s t e r ( Wr i te−only ) */
	unsigned int IDR; /** I n t e r r u p t Di sabl e Re g i s t e r ( Wr i te−only ) */
	unsigned int IMR; /** I n t e r r u p t Mask Re g i s t e r ( Read−only ) */
	unsigned int Reserved2[4]; /** Unused r e g i s t e r */
}TCCHAN;

typedef volatile struct _TC
{
	TCCHAN Channel_0;
	TCCHAN Channel_1;
	TCCHAN Channel_2;
	unsigned int BCR; /** Block Cont r o l Re g i s t e r ( Wr i te−only ) */
	unsigned int BMR; /** Block Mode Re g i s t e r ( Read−Wr i t e ) */
}TC;

/// ΕΝΑΡΞΗ ΑΡΧΙΚΟΠΟΙΗΣΗΣ ΣΥΣΤΗΜΑΤΟΣ
/// ΠΡΕΠΕΙ ΝΑ ΓΙΝΕΤΑΙ ΠΑΝΤΑ ΣΤΗΝ ΑΡΧΗ ΤΟΥ ΠΡΟΓΡΑΜΜΑΤΟΣ
#define STARTUP \
unsigned int _FIQtmp; \
/* ΑΠΑΡΑΙΤΗΤΟ ΓΙΑ ΠΡΟΣΠΕΛΑΣΗ ΜΝΗΜΗΣ ΣΥΣΤΗΜΑΤΟΣ */ \
int fd = open("/dev/mem", O_RDWR | O_SYNC); \
/* ΑΠΑΡΑΙΤΗΤΟ ΓΙΑ ΕΓΓΡΑΦΗ ΡΟΥΤΙΝΑΣ ΕΞΥΠΗΡΕΣΗΣ ΔΙΑΚΟΠΩΝ */ \
int fd2 = open("/proc/FIQ", O_RDWR | O_SYNC); \
/* ΕΝΕΡΓΟΠΟΙΗΣΗ ΔΙΚΑΙΩΜΑΤΩΝ ΠΡΟΣΠΕΛΑΣΗΣ ΣΤΗΝ*/ /** PIOA & AIC*/ \
char* mptr = mmap(0, 0x1000, PROT_READ | PROT_WRITE, \
MAP_SHARED, fd, 0xFFFFF000); \
/* ΑΠΑΡΑΙΤΗΤΟ ΓΙΑ ΠΡΟΣΠΕΛΑΣΗ ΤΩΝ*/ /**TIMERS*/ \
char* pptr = mmap(0, 0x1000, PROT_READ | PROT_WRITE, \
MAP_SHARED, fd, 0xFFFA0000); \
/* ΕΛΕΓΧΟΣ ΑΠΟΚΤΗΣΗΣ ΔΙΚΑΙΩΜΑΤΩΝ */ \
if(mptr == MAP_FAILED || pptr == MAP_FAILED){ \
close(fd); \
close(fd2); \
exit(1); \
} \
/* ΟΡΙΖΟΥΜΕ ΔΙΕΥΘΥΝΣΗ ΤΗΣ*/ /**PIOA*/ \
pioa = (PIO*)(mptr + 0x400); \
/* ΟΡΙΖΟΥΜΕ ΔΙΕΥΘΥΝΣΗ ΤΗΣ*/ /**AIC*/ \
aic = (AIC*)(mptr); \
/* ΟΡΙΖΟΥΜΕ ΔΙΕΥΘΥΝΣΗ ΤΟΥ*/ /**TC*/ \
tc = (TC*)(pptr); \
_FIQtmp = (unsigned int)FIQ_handler; \
write(fd2, &_FIQtmp, sizeof(unsigned int)); \
_FIQtmp = fcntl(STDIN_FILENO, F_GETFL, 0); \
_FIQtmp |= O_NONBLOCK; \
fcntl(STDIN_FILENO, F_SETFL, _FIQtmp)
/// ΛΗΞΗ ΑΡΧΙΚΟΠΟΙΗΣΗΣ
/// ΕΝΑΡΞΗ ΕΠΑΝΑΦΟΡΑΣ ΣΥΣΤΗΜΑΤΟΣ
/// ΠΡΕΠΕΙ ΝΑ ΓΙΝΕΤΑΙ ΠΑΝΤΑ ΣΤΟ ΤΕΛΟΣ ΤΟΥ ΠΡΟΓΡΑΜΜΑΤΟΣ
#define CLEANUP \
_FIQtmp = fcntl(STDIN_FILENO, F_GETFL, 0); \
_FIQtmp &= O_NONBLOCK; \
fcntl(STDIN_FILENO, F_SETFL, _FIQtmp); \
/* ΕΠΙΣΤΡΟΦΗ ΔΕΣΜΕΥΜΕΝΗΣ ΜΝΗΜΗΣ */ \
munmap(mptr, 0x1000); \
munmap(pptr, 0x1000); \
close(fd); \
close(fd2)
/// ΛΗΞΗ ΕΠΑΝΑΦΟΡΑΣ ΣΥΣΤΗΜΑΤΟΣ
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
