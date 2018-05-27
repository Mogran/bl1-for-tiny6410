
#include "io.h"

#define TINY6410_CLOCK_REGS (0x7e00f000)

#define APLL_MDIV	(400)
#define APLL_PDIV	(3)
#define APLL_SDIV	(2)

#define MPLL_MDIV	(400)
#define MPLL_PDIV	(3)
#define MPLL_SDIV	(2)

#define EPLL_MDIV	(32)
#define EPLL_PDIV	(1)
#define EPLL_SDIV	(3)

struct clock_regs_t {
	unsigned int apll_lock;
	unsigned int mpll_lock;
	unsigned int epll_lock;
	unsigned int apll_con;
	unsigned int mpll_con;
	unsigned int epll_con0;
	unsigned int epll_con1;
	unsigned int clk_src;
	unsigned int clk_div0;
	unsigned int clk_div1;
	unsigned int clk_div2;
	unsigned int clk_out;
};

static struct clock_regs_t* tiny6410_get_pll_register_base(void)
{
	return (struct clock_regs_t*)TINY6410_CLOCK_REGS;
}

/*
 *@Tiny6410的Fin = 12MHZ
 *
 *@descriptions : System Controller有两种模式，系统时钟控制与系统电源管理	
 * */
void tiny6410_clock_init(void)
{
	unsigned int regs_vals = 0;
	struct clock_regs_t *clock = tiny6410_get_pll_register_base();
	
	//设置时钟设置值之后锁存时间
	writel(clock->apll_lock, 0x0000ffff);
	writel(clock->mpll_lock, 0x0000ffff);
	writel(clock->epll_lock, 0x0000ffff);

	//设置APLL_Fout=400MHZ MPLL_Fout = 266MHZ EPLL_Fout = 48MHZ
	regs_vals = readl(clock->apll_con);
	regs_vals |= (1 << 31)|(APLL_MDIV << 16)|(APLL_PDIV << 8)|(APLL_SDIV << 0);
	writel(clock->apll_con, regs_vals);

	regs_vals = readl(clock->mpll_con);
	regs_vals |= (1 << 31)|(MPLL_MDIV << 16)|(MPLL_PDIV << 8)|(MPLL_SDIV << 0);
	writel(clock->mpll_con, regs_vals);

	regs_vals = readl(clock->epll_con0);
	regs_vals |= (1 << 31)|(EPLL_MDIV << 16)|(EPLL_PDIV << 8)|(EPLL_SDIV << 0);
	writel(clock->epll_con0, regs_vals);

	//(1 << 13)是为了让串口使用MPLL输出的时钟
	regs_vals = readl(clock->clk_src);
	regs_vals |= (1 << 13)|(1 << 2)|(1 << 1)|(1 << 0);
	writel(clock->clk_src, regs_vals);

	regs_vals = readl(clock->clk_div0);
	regs_vals &= ~((0xf << 24)|(0x3 << 18)|(0xf << 12)|(0x7 << 9)|(1 << 8)|(1 << 4)|(0xf << 0));
	regs_vals |= (3 << 18)|(3 << 24)|(3 << 12)|(1 << 8)|(0 << 9)|(0 << 4)|(0 << 0);
	writel(clock->clk_div0, regs_vals);	

	//初始化串口时钟66.6MHZ
	regs_vals = readl(clock->clk_div2);
	regs_vals |= (3 << 16);
	writel(clock->clk_div2, regs_vals);	
}
