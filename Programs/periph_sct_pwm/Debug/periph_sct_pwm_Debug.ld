/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008 - 2013 Code Red Technologies Ltd, 
 * Copyright 2015, 2018 NXP
 * (c) NXP Semiconductors 2013-2019
 * Generated linker script file for LPC54114J256
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.3.1 [Build 2233] [2019-02-20] on 23-May-2019 2:41:21 PM
 */

INCLUDE "periph_sct_pwm_Debug_library.ld"
INCLUDE "periph_sct_pwm_Debug_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
    /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

    } > MFlash256

    .text : ALIGN(4)
    {
       *(.text*)
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > MFlash256
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this. 
     */
    .ARM.extab : ALIGN(4) 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlash256

    __exidx_start = .;

    .ARM.exidx : ALIGN(4)
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlash256
    __exidx_end = .;
 
    _etext = .;
        
    /* DATA section for Ram1_64 */

    .data_RAM2 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$Ram1_64)
        *(.data.$RAM2*)
        *(.data.$Ram1_64*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM2 = .) ;
     } > Ram1_64 AT>MFlash256
    /* DATA section for Ram2_32 */

    .data_RAM3 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM3 = .) ;
        *(.ramfunc.$RAM3)
        *(.ramfunc.$Ram2_32)
        *(.data.$RAM3*)
        *(.data.$Ram2_32*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM3 = .) ;
     } > Ram2_32 AT>MFlash256
    /* DATA section for RamX_32 */

    .data_RAM4 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM4 = .) ;
        *(.ramfunc.$RAM4)
        *(.ramfunc.$RamX_32)
        *(.data.$RAM4*)
        *(.data.$RamX_32*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM4 = .) ;
     } > RamX_32 AT>MFlash256
    /* MAIN DATA SECTION */
    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > Ram0_64

    /* Main DATA section (Ram0_64) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       *(vtable)
       *(.ramfunc*)
       *(.data*)
       . = ALIGN(4) ;
       _edata = . ;
    } > Ram0_64 AT>MFlash256

    /* BSS section for Ram1_64 */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       *(.bss.$RAM2*)
       *(.bss.$Ram1_64*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
    } > Ram1_64 

    /* BSS section for Ram2_32 */
    .bss_RAM3 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       *(.bss.$RAM3*)
       *(.bss.$Ram2_32*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
    } > Ram2_32 

    /* BSS section for RamX_32 */
    .bss_RAM4 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
       *(.bss.$RAM4*)
       *(.bss.$RamX_32*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM4 = .) ;
    } > RamX_32 

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > Ram0_64

    /* NOINIT section for Ram1_64 */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM2*)
       *(.noinit.$Ram1_64*)
       . = ALIGN(4) ;
    } > Ram1_64 

    /* NOINIT section for Ram2_32 */
    .noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM3*)
       *(.noinit.$Ram2_32*)
       . = ALIGN(4) ;
    } > Ram2_32 

    /* NOINIT section for RamX_32 */
    .noinit_RAM4 (NOLOAD) : ALIGN(4)
    {
       *(.noinit.$RAM4*)
       *(.noinit.$RamX_32*)
       . = ALIGN(4) ;
    } > RamX_32 

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*) 
         . = ALIGN(4) ;
        _end_noinit = .;
    } > Ram0_64
    PROVIDE(_pvHeapStart = DEFINED(__user_heap_base) ? __user_heap_base : .);
    PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_Ram0_64 - 0);

    /* ## Create checksum value (used in startup) ## */
    PROVIDE(__valid_user_code_checksum = 0 - 
                                         (_vStackTop 
                                         + (ResetISR + 1) 
                                         + (NMI_Handler + 1) 
                                         + (HardFault_Handler + 1) 
                                         + (( DEFINED(MemManage_Handler) ? MemManage_Handler : 0 ) + 1)   /* MemManage_Handler may not be defined */
                                         + (( DEFINED(BusFault_Handler) ? BusFault_Handler : 0 ) + 1)     /* BusFault_Handler may not be defined */
                                         + (( DEFINED(UsageFault_Handler) ? UsageFault_Handler : 0 ) + 1) /* UsageFault_Handler may not be defined */
                                         ) );

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
}