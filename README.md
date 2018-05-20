# Zynq_UDP

Author

Del Hatch

** Communicating over UDP

The purpose of this project is to demostrate data transfers over UDP using the Zedboard. This can be used on the MicroZed and other Zynq-based boards with minor modifications.

** Build a Zynq system using Vivado

Using the figure below as a guide, build a Zynq system. The AXI Interconnect, Processor Reset, and GPIO modules are optional, but I like to put them in for command.control/debugging later.

![screenshot](https://github.com/delhatch/Zynq_UDP/blob/master/system.JPG)

You can use all of the system defaults, peripheral auto-address assignments, and system configuration defaults -- no need to customize anything.

After you build the system and export the hardware (including the bit file) launch the SDK.

** SDK and software

After the SDK opens, click File -> New -> Application Project.

Give the project a name, then click Next.

Select "lwIP Echo Server" from the list of Available Templates, and Finish.

At this point you can compile, load and run the Echo Server on the Zedboard. I use PuTTY to see it working.

Launch PuTTY, type in the IP address of the Zedboard defined in the main.c file, set the Port value to 7, and select "Telnet" as the connection type. In the window that opens, you can type letters and see them echoed back to PuTTY.

** Changing the Echo Server to use UDP

The default lwIP Echo Server uses TCP. To convert it to use UDP instead, replace the supplied main.c with the main.c in this Github repository. Also, replace the echo.c file.

Also, download the includes.h file and add it to your project.

Copy the files into your project's <project>.sdk/<project>/src directory. Then in the SDK, highlight the <SDK project> line in the "Project Explorer" frame, and hit F5 to refresh.

** Compile and run

Now compile and run the code. As the code runs, in the connected terminal program, you will see this:

![screenshot](https://github.com/delhatch/Zynq_UDP/blob/master/terminal.JPG)

The dots along the bottom indicate that the Zedboard is sending a UDP packet. This happens once every 500 mSeconds. The packet consists of a single integer with a value of 0x45.

To see the packets being sent, use Wireshark.

There are many ways to transmit UDP packets to the Zedboard. I used the VLC media player and set it to stream a .mpg file over UDP. Here's how to do that:

Launch VLC and click Media -> Stream...

On the File tab, click "+Add" and select a media file. I use a .mpg video file. Click the Stream button.

Click Next. For the Destination Setup, pull-down the New destination box. Select UDP (legacy). Click Add. Type in the IP address of the Zedboard and set the Port to 7.

Click Next. I un-select "Activate Transcoding" but it does not matter for this purpose.

Click Next, and then Stream.

In ther terminal program you will see a lot of messages showing you the length of the UDP datagrams received by the Zedboard, from the VLC program.

** Improvements

This project is mainly a demonstration of how to use UDP to send and receive data using a Zedboard or other Zynq board.

I will be using it to stream media from the Zedboard to a PC, and using VLC to view the media stream.

** Credit

Lance Simms posted a very good, and complicated, project that uses UDP here: http://lancesimms.com/Xilinx/MicroZed_UDP_Server_for_Waveform_Centroiding_Table_Of_Contents.html

My project reduces that code base to the fundamental UDP principles to provide an easily extended platform for custom projects.

