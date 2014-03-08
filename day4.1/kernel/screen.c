#include<header.h>

void clear_screen(char color) //15:pure white
{
  int i;
  for(i=0xa0000;i<0xaffff;i++)
  {
  write_mem8(i,color);  //if we write 15 ,all pixels color will be white,15 mens pure white ,so the screen changes into white

  }
}

void color_screen(char color) //15:pure white
{
  int i;
  color=color;
  for(i=0xa0000;i<0xaffff;i++)
  {
  write_mem8(i,i&0x0f);  //if we write 15 ,all pixels color will be white,15 mens pure white ,so the screen changes into white

  }
}