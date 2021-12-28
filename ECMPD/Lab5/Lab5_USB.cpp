#include <iostream>
#include <libusb.h>
#include <stdio.h>

using namespace std;

void print_info(libusb_device *dev);

int main()
{
 libusb_device **devs;
 libusb_context *ctx = NULL;
 int r;
 ssize_t cnt; 
 ssize_t i;
 r = libusb_init(&ctx); 
 if(r < 0)
 {
 fprintf(stderr, "РћС€РёР±РєР°: РёРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РЅРµ РІС‹РїРѕР»РЅРµРЅР°, РєРѕРґ: %d.\n", r);
 return 1;
 }

 libusb_set_debug(ctx, 3);
 cnt = libusb_get_device_list(ctx, &devs);

 if(cnt < 0)
 {
  fprintf(stderr, "РћС€РёР±РєР°: СЃРїРёСЃРѕРє USB СѓСЃС‚СЂРѕР№СЃС‚РІ РЅРµ РїРѕР»СѓС‡РµРЅ.\n", r);
  return 1;
 }
 printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
 for(i = 0; i < cnt; i++) //С†РёРєР» РїРµСЂРµР±РѕСЂР° РІСЃРµС… СѓСЃС‚СЂРѕР№СЃС‚РІ
 {
    print_info(devs[i]); // РїРµС‡Р°С‚СЊ РїР°СЂР°РјРµС‚СЂРѕРІ СѓСЃС‚СЂРѕР№СЃС‚РІР°
 }
  printf("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
 libusb_free_device_list(devs, 1);
 libusb_exit(ctx); // Р·Р°РІРµСЂС€РёС‚СЊ СЂР°Р±РѕС‚Сѓ СЃ Р±РёР±Р»РёРѕС‚РµРєРѕР№ libusb,
                   // Р·Р°РєСЂС‹С‚СЊ СЃРµСЃСЃРёСЋ СЂР°Р±РѕС‚С‹ СЃ libusb
 return 0;
}


void print_info(libusb_device *dev)
{
    libusb_device_descriptor descriptor; // device descriptor
    int r = libusb_get_device_descriptor(dev, &descriptor);
    if(r < 0)
    {
        fprintf(stderr, "РћС€РёР±РєР°: РґРµСЃРєСЂРёРїС‚РѕСЂ СѓСЃС‚СЂРѕР№СЃС‚РІР° РЅРµ РїРѕР»СѓС‡РµРЅ");
        return;
    }

    printf("РљР»Р°СЃСЃ СѓСЃС‚СЂРѕР№СЃС‚РІР°: %d\n", (int)descriptor.bDeviceClass);
    printf("РРґРµРЅС‚РёС„РёРєР°С‚РѕСЂ РїСЂРѕРёР·РІРѕРґРёС‚РµР»СЏ: %d\n", descriptor.idVendor);
    printf("РРґРµРЅС‚РёС„РёРєР°С‚РѕСЂ РёР·РґРµР»РёСЏ: %d\n", descriptor.idProduct);
    
    libusb_device_handle* handle;
    libusb_open(dev, &handle);
    
    unsigned char serial_number[255];
    
    r  = libusb_get_string_descriptor_ascii(handle, descriptor.iSerialNumber, serial_number, sizeof(serial_number));
    if(r < 0)
    {
        printf("РќРµ СѓРґР°Р»РѕСЃСЊ РЅР°Р№С‚Рё СЃРµСЂРёР№РЅС‹Р№ РЅРѕРјРµСЂ\n");
        return;
    }
    printf("РЎРµСЂРёР№РЅС‹Р№ РЅРѕРјРµСЂ:%s\n ", serial_number);

    
    libusb_close(handle);
}
