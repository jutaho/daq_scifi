#include "displayserver.h"

DisplayServer::DisplayServer(QObject *parent) : QObject(parent)
{
}

DisplayServer::~DisplayServer()
{
    unsetup();
}

//********************************************

PlaneConfig* DisplayServer::findPlane(int plane_nr)
{
    for (int plane = 0; plane < planeConfig.length(); plane++)
    {
        if (planeConfig[plane]->nr == plane_nr)
            return planeConfig[plane];
    }

    // Create new plane if not found
    PlaneConfig* new_plane = new PlaneConfig;
    new_plane->nr = plane_nr;
    new_plane->name = QString("Plane %1").arg(plane_nr);
    new_plane->nr_devices = 0;
    new_plane->nr_sensors = 0;
    planeConfig.append(new_plane);
    return new_plane;
}

void DisplayServer::setup(HW* hw)
{
    unsetup();  // Ensure previous configuration is cleared.
    theHW = hw;

    for (int dev_nr = 0; dev_nr < theHW->devices.length(); dev_nr++)
    {
        PlaneConfig* current_plane = findPlane(theHW->devices[dev_nr]->deviceConfig.plane);
        current_plane->devices.append(theHW->devices[dev_nr]);
        current_plane->nr_devices++;
        current_plane->nr_sensors += theHW->devices[dev_nr]->deviceConfig.nr_sensors;
    }
}

void DisplayServer::unsetup()
{
    hide();
    for (int plane_nr = 0; plane_nr < planeConfig.length(); plane_nr++)
    {
        delete planeConfig[plane_nr];
        planeConfig[plane_nr] = NULL;
    }
    planeConfig.clear();
}

//********************************************

void DisplayServer::show()
{
    hide();
    displays.clear();
    for (int plane = 0; plane < planeConfig.length(); plane++)
    {
        BPMDisplay* newDisplay = new BPMDisplay;
        newDisplay->setTitle(planeConfig[plane]->name);
        newDisplay->show();
        displays.append(newDisplay);
    }
    active = 1;
}

void DisplayServer::hide()
{
    if (active)
    {
        for (int plane = 0; plane < displays.length(); plane++)
        {
            displays[plane]->close();
            delete displays[plane];
        }
        displays.clear();
        active = 0;
    }
}

void DisplayServer::plot()
{
    if (!active)
        return;

    QVector<BufferData> lastFrame = theHW->eventBuilder.getLastFrame();
    if (lastFrame.length() == 0)
        return;

    for (int plane = 0; plane < planeConfig.length(); plane++)
    {
        // Initialize display buffers
        displays[plane]->rawBuffer.resize(planeConfig[plane]->nr_sensors * 64);
        displays[plane]->calBuffer.resize(planeConfig[plane]->nr_sensors * 64);

        // Fill with data from each device in the current plane
        int current_base = 0;
        for (int dev_nr = 0; dev_nr < planeConfig[plane]->nr_devices; dev_nr++)
        {
            int dev_id = planeConfig[plane]->devices[dev_nr]->deviceConfig.device_id;
            int nr_channels = planeConfig[plane]->devices[dev_nr]->deviceConfig.nr_channels();
            if (nr_channels > lastFrame[dev_id].buffer_size)
                nr_channels = lastFrame[dev_id].buffer_size;    // Check if there's actually data in the buffer
            // Note: device order mapping is not yet implemented!        

            for (int i = 0; i < planeConfig[plane]->nr_sensors * 64; ++i) {
                displays[plane]->rawBuffer[current_base + i] = lastFrame[dev_id].raw_data[i];
                displays[plane]->calBuffer[current_base + i] = lastFrame[dev_id].cal_data[i];
            }
        }
        // Plot the data on the display
      displays[plane]->plot(displays[plane]->rawBuffer, displays[plane]->calBuffer);
    }
}

int DisplayServer::isActive()
{
    return active;
}
