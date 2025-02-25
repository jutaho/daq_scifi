::flash_loader
C:\intelFPGA_lite\23.1std\quartus\bin64\quartus_pgm.exe -c "USB-BlasterII [USB-1]" -m JTAG -o "p;C:\flash_fpga\flash_loader.sof@1"

::erase and program flash by ext_flash.pof; the location of ext_flash is specificed in ChainFlash.cdf
C:\intelFPGA_lite\23.1std\quartus\bin64\quartus_pgm.exe -c "USB-BlasterII [USB-1]" C:\flash_fpga\ChainFlash.cdf

C:\intelFPGA_lite\23.1std\quartus\bin64\quartus_pgm.exe -c "USB-BlasterII [USB-1]" -m JTAG -o "p;C:\flash_fpga\hit20v3.pof@1"

::jtagconfig.exe -n 
::show the devices on the JTAG chain

::jtagconfig.exe -n 
::show the devices on the JTAG chain