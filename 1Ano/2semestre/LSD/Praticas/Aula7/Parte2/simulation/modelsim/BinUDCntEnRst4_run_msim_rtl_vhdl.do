transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {C:/Users/marci/Desktop/Universidade/1Ano/2semestre/LSD/Praticas/Aula7/Parte2/BinUDCntEnRst4.vhd}
