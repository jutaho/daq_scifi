#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

class DeviceConfig
{
public:
    unsigned char own_ip[4];
    unsigned char device_ip[4];
    int device_id;
    int hardware_ver; // always 2
    int master;
    int plane;
    int position;
    int nr_sensors;
    int period;
    int tint;
    int master_delay;
    int slave_delay;
    int gain;
    int dma_bunch;
    int eth_bunch;
    int threshold;

    DeviceConfig()
        : own_ip{10,0,7,1}, device_ip{10,0,7,2},
        device_id(0), hardware_ver(2), master(1), plane(0),
        position(0), nr_sensors(0), period(65535), tint(1),
        master_delay(1), slave_delay(1), gain(0),
        dma_bunch(1), eth_bunch(1), threshold(1)
    {}

    int max_sensors() const { return 5; }
    int max_channels() const { return 64 * max_sensors(); }
    int nr_channels() const { return 64 * nr_sensors; }
};

#endif // DEVICECONFIG_H
