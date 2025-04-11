.PHONY: all
.SILENT: clean

TARGET = your_driver  # Поставьте имя своего модуля ядра, больше ничего не меняйте
obj-m := $(TARGET).o

CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

CC = $(shell grep CONFIG_CC_VERSION /boot/config-$(CURRENT) | cut -d'"' -f2 | awk '{print $$1}')

all:
	$(MAKE) CC=$(CC) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.cmd .*.cmd *.mod .*.mod *.mod.* *.o *.order *.symvers
