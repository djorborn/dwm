# dwm

## More info in the wiki

I am tring to keep track of everything I do here. I have had to start from scratch a few times becuase I forget what I did in what order and when. This may help? I will see.
Keeping track of my take on each patch in the wiki.

### Patches
1. [attachbottom](https://dwm.suckless.org/patches/attachbottom/)
  - This is the first patch and worked no problem.
2. [ewmhtags](http://dwm.suckless.org/patches/ewmhtags/)
  - This is a just incase for me.
3. [ispermanent](http://dwm.suckless.org/patches/ispermanent/)
  - this comes in handy
   
4. [pertag](http://dwm.suckless.org/patches/pertag/)
  - This is very useful to me.
  
5. [restartsig](http://dwm.suckless.org/patches/restartsig/)
  - restart dwm in place, this is so awesome!!, this is most useful as the first patch.
  
6. [sticky](http://dwm.suckless.org/patches/sticky/)
  - this with ispermanent works like a charm.
  
7. [systray](http://dwm.suckless.org/patches/systray/)
  - System Tray, A must for me, for now anyway
  
8. [stackmfact](http://dwm.suckless.org/patches/stackmfact/)
  - vertically resize clients in the stack

### Did Not Keep
1. [activetagindicatorbar](http://dwm.suckless.org/patches/activetagindicatorbar/)
 - I thought I would like the look but I found I like the square better.
2. [focusonclick](http://dwm.suckless.org/patches/focusonclick/)
 - This one seemed to make it so I couldn't resize or move floating windows. I ended up just commenting out a line in dwm.c, more info in the wiki.


## Building
Still using make, the compiler has been changed to [tcc](https://bellard.org/tcc/). 

## Install
Also nothing changed, `sudo make clean install`
