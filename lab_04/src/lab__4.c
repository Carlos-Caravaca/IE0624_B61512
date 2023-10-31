
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "clock.h"
#include "console.h"
#include "sdram.h"
#include "lcd-spi.h"
#include "gfx.h"
#include <inttypes.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/ltdc.h>
#include <libopencm3/stm32/usart.h>


// Definiciones de los pines de LED y LCD (ajusta según tu hardware)
#define LBLUE GPIOE, GPIO8
#define LRED GPIOE, GPIO9
#define LORANGE GPIOE, GPIO10
#define LGREEN GPIOE, GPIO11
#define LBLUE2 GPIOE, GPIO12
#define LRED2 GPIOE, GPIO13
#define LORANGE2 GPIOE, GPIO14
#define LGREEN2 GPIOE, GPIO15

#define LD4 GPIOE, GPIO8
#define LD3 GPIOE, GPIO9
#define LD5 GPIOE, GPIO10
#define LD7 GPIOE, GPIO11
#define LD9 GPIOE, GPIO12
#define LD10 GPIOE, GPIO13
#define LD8 GPIOE, GPIO14
#define LD6 GPIOE, GPIO15
uint16_t read_reg(uint8_t reg);
void write_reg(uint8_t reg, uint8_t value);
void read_xyz(int16_t vecs[3]);
int print_decimal(int num);

// Definición del giroscopio
#define MEMS_CS GPIOE, GPIO3

static void spi_setup(void)
{
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOE);

    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
    gpio_set(GPIOE, GPIO3);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO5 | GPIO6 | GPIO7);
    gpio_set_af(GPIOA, GPIO_AF5, GPIO5 | GPIO6 | GPIO7);

    spi_set_master_mode(SPI1);
    spi_set_baudrate_prescaler(SPI1, SPI_CR1_BR_FPCLK_DIV_32);
    spi_set_clock_polarity_0(SPI1);
    spi_set_clock_phase_0(SPI1);
    spi_set_full_duplex_mode(SPI1);
    spi_set_unidirectional_mode(SPI1);
    // spi_set_data_size(SPI1, SPI_CR1_DFF_8BIT);
    spi_enable_software_slave_management(SPI1);
    spi_send_msb_first(SPI1);
    spi_set_nss_high(SPI1);
    // spi_fifo_reception_threshold(SPI1, SPI_CR2_FRF);
    // SPI_I2SCFGR(SPI1) &= ~SPI_I2SCFGR_I2SMOD;
    spi_enable(SPI1);
}

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOE);
	gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
		GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 |
		GPIO14 | GPIO15);
}
static void usart_setup(void)
{
	/* Enable clocks for GPIO port A (for GPIO_USART2_TX) and USART2. */
	rcc_periph_clock_enable(RCC_USART2);
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2| GPIO3);

	/* Setup UART parameters. */
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX_RX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART2);
}
#define GYR_RNW			(1 << 7) /* Write when zero */
#define GYR_MNS			(1 << 6) /* Multiple reads when 1 */
#define GYR_WHO_AM_I		0x0F
#define GYR_OUT_TEMP		0x26
#define GYR_STATUS_REG		0x27
#define GYR_CTRL_REG1		0x20
#define GYR_CTRL_REG1_PD	(1 << 3)
#define GYR_CTRL_REG1_XEN	(1 << 1)
#define GYR_CTRL_REG1_YEN	(1 << 0)
#define GYR_CTRL_REG1_ZEN	(1 << 2)
#define GYR_CTRL_REG1_BW_SHIFT	4
#define GYR_CTRL_REG4		0x23
#define GYR_CTRL_REG4_FS_SHIFT	4

#define GYR_OUT_X_L		0x28
#define GYR_OUT_X_H		0x29
#define GYR_OUT_Y_L     0x2A
#define GYR_OUT_Y_H     0x2B
#define GYR_OUT_Z_L     0x2C
#define GYR_OUT_Z_H     0x2D

int main(void)
{
    char gyr_x_final[20];
    char gyr_y_final[20];
    char gyr_z_final[20];

    int16_t gyr_x;
    int16_t gyr_y;
    int16_t gyr_z;
	
	clock_setup();
	gpio_setup();
	usart_setup();
	spi_setup();
    gpio_clear(GPIOE, GPIO3);
	spi_send(SPI1, GYR_CTRL_REG1);
	spi_read(SPI1);
	spi_send(SPI1, GYR_CTRL_REG1_PD | GYR_CTRL_REG1_XEN |
			GYR_CTRL_REG1_YEN | GYR_CTRL_REG1_ZEN |
			(3 << GYR_CTRL_REG1_BW_SHIFT));
	spi_read(SPI1);
	gpio_set(GPIOE, GPIO3);

	gpio_clear(GPIOE, GPIO3);
	spi_send(SPI1, GYR_CTRL_REG4);
	spi_read(SPI1);
	spi_send(SPI1, (1 << GYR_CTRL_REG4_FS_SHIFT));
	spi_read(SPI1);
	gpio_set(GPIOE, GPIO3);
    console_setup(115200);
    sdram_init();
    lcd_spi_init();

    console_puts("LCD Initialized\n");
    console_puts("Should have a checker pattern, press any key to proceed\n");
    msleep(2000);

    gfx_init(lcd_draw_pixel, 240, 320);
    gfx_fillScreen(LCD_GREY);
    gfx_fillRoundRect(10, 10, 220, 220, 5, LCD_WHITE);
    gfx_drawRoundRect(10, 10, 220, 220, 5, LCD_RED);
    gfx_fillCircle(20, 250, 10, LCD_BLUE);
    gfx_fillCircle(70, 250, 10, LCD_RED);
    gfx_fillCircle(120, 250, 10, LCD_GREEN);
    gfx_fillCircle(170, 250, 10, LCD_BLUE);
    gfx_fillCircle(220, 250, 10, LCD_RED);
    gfx_fillCircle(270, 250, 10, LCD_GREEN);
    gfx_setTextSize(1);
    gfx_setCursor(15, 25);
    gfx_puts("Carlos Caravaca. B61512");
	gfx_setCursor(15, 45);
    gfx_puts("Erick Sancho. B87388");
    gfx_setTextSize(1);
    gfx_setCursor(15, 70);
    gfx_puts("Laboratorio 04");
    gfx_setCursor(15, 90);
    gfx_puts("Sismografo");
    lcd_show_frame();

    console_puts("Now it has a bit of structured graphics.\n");
    console_puts("Press a key for some simple animation.\n");
    msleep(5000);

    // gfx_setTextColor(LCD_YELLOW, LCD_WHITE);

    while (1)
    {
        gfx_fillScreen(LCD_BLACK);
		// gfx_fillScreen(LCD_GREY);
		gfx_fillRoundRect(10, 10, 220, 220, 5, LCD_BLACK);
		gfx_drawRoundRect(10, 10, 220, 220, 5, LCD_RED);
		gfx_drawLine(15, 260, 220, 260, LCD_GREEN);
		gfx_drawLine(15, 280, 220, 280, LCD_BLUE);
		gfx_drawLine(15, 300, 220, 300, LCD_YELLOW);
		
		gfx_setTextColor(LCD_RED, LCD_BLACK);
        gfx_setCursor(15, 36);
        gfx_puts("======> SISMOGRAFO <======");

		gfx_setTextColor(LCD_GREEN, LCD_BLACK);
		// simulacion de como se deberia ver el dato
		gfx_setCursor(50, 100);
		gfx_puts("Bateria = 5.46 V");

        // Muestra los datos del giroscopio en la pantalla
        gfx_setCursor(50, 120);
        gfx_puts("Datos eje X: ");
        gfx_setCursor(50, 140);
        gfx_puts("Datos eje Y: ");
        gfx_setCursor(50, 160);
        gfx_puts("Datos eje Z: ");
        gfx_puts("\n");

		
        gpio_clear(GPIOE, GPIO3);
		spi_send(SPI1, GYR_OUT_X_L | 0x80);
		spi_read(SPI1);
		spi_send(SPI1, 0);
		gyr_x=spi_read(SPI1);
		gpio_set(GPIOE, GPIO3);

		gpio_clear(GPIOE, GPIO3);
		spi_send(SPI1, GYR_OUT_X_H | 0x80);
		spi_read(SPI1);
		spi_send(SPI1, 0);
		gyr_x|=spi_read(SPI1) << 8;
		sprintf(gyr_x_final, "%d", gyr_x);
		gfx_setCursor(165, 120);
		gfx_puts(gyr_x_final);
		// my_usart_print_int(USART2, (gyr_x));
		gpio_set(GPIOE, GPIO3);

		gpio_clear(GPIOE, GPIO3);
		spi_send(SPI1, GYR_OUT_Y_L | 0x80);
		spi_read(SPI1);
		spi_send(SPI1, 0);
		gyr_y=spi_read(SPI1);
		gpio_set(GPIOE, GPIO3);

		gpio_clear(GPIOE, GPIO3);
		spi_send(SPI1, GYR_OUT_Y_H | 0x80);
		spi_read(SPI1);
		spi_send(SPI1, 0);
		gyr_y|=spi_read(SPI1) << 8;
		sprintf(gyr_y_final, "%d", gyr_y);
		gfx_setCursor(165, 140);
		gfx_puts(gyr_y_final);
		// my_usart_print_int(USART2, (gyr_x));
		gpio_set(GPIOE, GPIO3);

		gpio_clear(GPIOE, GPIO3);
		spi_send(SPI1, GYR_OUT_Z_L | 0x80);
		spi_read(SPI1);
		spi_send(SPI1, 0);
		gyr_z=spi_read(SPI1);
		gpio_set(GPIOE, GPIO3);

		gpio_clear(GPIOE, GPIO3);
		spi_send(SPI1, GYR_OUT_Z_H | 0x80);
		spi_read(SPI1);
		spi_send(SPI1, 0);
		gyr_z|=spi_read(SPI1) << 8;
		sprintf(gyr_z_final, "%d", gyr_z);
		gfx_setCursor(165, 160);
		gfx_puts(gyr_z_final);
		// my_usart_print_int(USART2, (gyr_x));
		gpio_set(GPIOE, GPIO3);

        lcd_show_frame();
        msleep(100);
    }
}

