IdlePrevent
===========

I created IdlePrevent to prevent my computer at work from locking itself automatically. In some corporate environments
policies force Windows to lock your computer if you are idle for a set amount of time. I find having to unlock your computer
every 5 minutes or so can be a bit annoying, so I took it upon myself to make a simple application to solve this.

I'm currently planning on porting the source code to something a bit more universal (MinGW32) since compiling under
Visual Studio 2008 will usually require more recent versions of Windows and in some cases even a redistributable
package to be installed. 