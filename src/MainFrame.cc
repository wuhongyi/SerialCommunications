// MainFrame.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 1月  1 20:05:32 2017 (+0800)
// Last-Updated: 日 1月  1 21:09:38 2017 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 8
// URL: http://wuhongyi.cn 

#include "MainFrame.hh"

#include <stdio.h>  /*标准输入输出定义*/
#include <stdlib.h> /*标准函数库定义*/
#include <unistd.h> /*Unix 标准函数定义*/
#include <sys/types.h> 
#include <sys/stat.h>   
#include <fcntl.h>  /*文件控制定义*/
#include <termios.h>/*POSIX 终端控制定义*/
#include <errno.h>  /*错误号定义*/

#include <ctime>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MainFrame::MainFrame(const TGWindow * p)
: TGMainFrame(p)
{

  TGTab *TabPanel = new TGTab(this);
  this->AddFrame(TabPanel, new TGLayoutHints(kLHintsBottom | kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
  Tab1 = TabPanel->AddTab("PB-5");
  MakeFoldPanelPB_5(Tab1);


  

  // What to clean up in dtor
  SetCleanup(kDeepCleanup);
  SetWindowName("PKU PB-5");
  MapSubwindows();
  Resize(GetDefaultSize());
  MapWindow();
}


MainFrame::~MainFrame()
{
  // Clean up all widgets, frames and layouthints that were used
  Cleanup();

}


void MainFrame::CloseWindow()
{


  gApplication->Terminate(0);
}  

void MainFrame::MakeFoldPanelPB_5(TGCompositeFrame *TabPanel)
{
  TGGroupFrame *initboaedgroup = new TGGroupFrame(TabPanel,"Connect");
  TabPanel->AddFrame(initboaedgroup,new TGLayoutHints(kLHintsExpandX|kLHintsTop));

  TGHorizontalFrame *initboaed = new TGHorizontalFrame(initboaedgroup);
  initboaedgroup->AddFrame(initboaed, new TGLayoutHints(kLHintsExpandX | kLHintsTop,0/*left*/,0/*right*/,0/*top*/,0/*bottom*/));

  connectStyle = new TGComboBox(initboaed,-1);
  initboaed->AddFrame(connectStyle, new TGLayoutHints(kLHintsLeft, 5, 5, 2, 2));
  connectStyle->AddEntry("USB0",0);
  connectStyle->AddEntry("USB1",1);
  connectStyle->AddEntry("USB2",2);
  connectStyle->AddEntry("USB3",3);
  connectStyle->AddEntry("USB4",4);
  connectStyle->Select(0);
  connectStyle->Resize(100,20);

  connectButton = new TGTextButton(initboaed,"Connect",CONNECTBUTTON);
  initboaed->AddFrame(connectButton, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 10,0, 0));
  connectButton->SetFont("-adobe-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1", false);
  connectButton->SetTextColor(0x0000ff, false);
  connectButton->Associate(this);
  connectButton->SetEnabled(1);

  DeleteButton = new TGTextButton(initboaed,"DeleteConnect",DELETEBUTTON);
  initboaed->AddFrame(DeleteButton, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 10,0, 0));
  DeleteButton->SetFont("-adobe-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1", false);
  DeleteButton->SetTextColor(0xff0000, false);
  DeleteButton->Associate(this);
  DeleteButton->SetEnabled(0);

  StateMsg = new TGTextEntry(initboaed,
			     new TGTextBuffer(100), -1,
			     StateMsg->GetDefaultGC()(),
			     StateMsg->GetDefaultFontStruct(),
			     kRaisedFrame | kDoubleBorder,
			     GetWhitePixel());
  initboaed->AddFrame(StateMsg, new TGLayoutHints(kLHintsExpandX | kLHintsLeft, 10, 0, 0, 0));
  StateMsg->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  StateMsg->SetTextColor(0xd15fee, false);
  StateMsg->SetText("Please enter Connect");
  // StateMsg->Resize(100, 12);
  StateMsg->SetEnabled(kFALSE);
  StateMsg->SetFrameDrawn(kFALSE);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int MainFrame::OpenDev(char *Dev)
{
  int fd = open(Dev, O_RDWR | O_NOCTTY); 
  //| O_NOCTTY | O_NDELAY    
  if (-1 == fd)    
    {             
      return -1;        
    }    
  else    
    return fd;
}

/**
 *@brief  设置串口通信速率
 *@param  fd     类型 int  打开串口的文件句柄
 *@param  speed  类型 int  串口速度
 *@return  void
 */
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
		    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300, 38400,  
		  19200,  9600, 4800, 2400, 1200,  300, };

void MainFrame::set_speed(int fd, int speed)
{
  int   i; 
  int   status; 
  struct termios   Opt;
  tcgetattr(fd, &Opt); 
  for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    { 
      if  (speed == name_arr[i])
	{     
	  tcflush(fd, TCIOFLUSH);     
	  cfsetispeed(&Opt, speed_arr[i]);  
	  cfsetospeed(&Opt, speed_arr[i]);   
	  status = tcsetattr(fd, TCSANOW, &Opt);  
	  if  (status != 0)
	    {        
	      perror("tcsetattr fd");  
	      return;     
	    }    
	  tcflush(fd,TCIOFLUSH);   
	}  
    }
}

/**
 *@brief   设置串口数据位，停止位和效验位
 *@param  fd     类型  int  打开的串口文件句柄
 *@param  databits 类型  int 数据位   取值 为 7 或者8
 *@param  stopbits 类型  int 停止位   取值为 1 或者2
 *@param  parity  类型  int  效验类型 取值为N,E,O,,S
 */
int MainFrame::set_Parity(int fd,int databits,int stopbits,int parity)
{ 
  struct termios options; 
  if  ( tcgetattr( fd,&options)  !=  0)
    { 
      perror("SetupSerial 1");     
      return -1;  
    }
  options.c_cflag &= ~CSIZE; 
  switch (databits) /*设置数据位数*/
    {   
    case 7:        
      options.c_cflag |= CS7; 
      break;
    case 8:     
      options.c_cflag |= CS8;
      break;   
    default:    
      fprintf(stderr,"Unsupported data size\n");
      return -1;  
    }
  switch (parity) 
    {   
    case 'n':
    case 'N':    
      options.c_cflag &= ~PARENB;   /* Clear parity enable */
      options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
      break;  
    case 'o':   
    case 'O':     
      options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/  
      options.c_iflag |= INPCK;             /* Disnable parity checking */ 
      break;  
    case 'e':  
    case 'E':   
      options.c_cflag |= PARENB;     /* Enable parity */    
      options.c_cflag &= ~PARODD;   /* 转换为偶效验*/     
      options.c_iflag |= INPCK;       /* Disnable parity checking */
      break;
    case 'S': 
    case 's':  /*as no parity*/   
      options.c_cflag &= ~PARENB;
      options.c_cflag &= ~CSTOPB;
      break;  
    default:   
      fprintf(stderr,"Unsupported parity\n");    
      return -1;  
    }  
  /* 设置停止位*/  
  switch (stopbits)
    {   
    case 1:    
      options.c_cflag &= ~CSTOPB;  
      break;  
    case 2:    
      options.c_cflag |= CSTOPB;  
      break;
    default:    
      fprintf(stderr,"Unsupported stop bits\n");  
      return -1; 
    } 
  /* Set input parity option */ 
  if (parity != 'n')   
    options.c_iflag |= INPCK; 
  tcflush(fd,TCIFLUSH);

  options.c_iflag &= ~(IGNBRK | IGNCR | INLCR | ICRNL | IUCLC |
		       IXANY | IXON | IXOFF | INPCK | ISTRIP);
  options.c_iflag |= (BRKINT | IGNPAR);
  options.c_oflag &= ~OPOST;
  options.c_lflag &= ~(XCASE|ECHONL|NOFLSH);
  options.c_lflag &= ~(ICANON | ISIG | ECHO);//在用write发送数据时没有键入回车，信息就将发送不出去的情况，这主要是因为我们在输出输入时是按照 规范模式接受到回车或者换行才发送，而很多情况我们是不需要回车和换行的，这时，应当切换到行方式输入;不经处理直接发送。
  options.c_cflag |= CREAD;
  options.c_cc[VTIME] = 5;
  options.c_cc[VMIN] = 1;

  if (tcsetattr(fd,TCSANOW,&options) != 0)   
    { 
      perror("SetupSerial 3");   
      return -1;  
    } 
  return 0;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Bool_t MainFrame::ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
{
  // WidgetMessageTypes.h

  // System predefined widget message types. Message types are constants  
  // that indicate which widget sent the message and by which widget      
  // function (sub-message). Make sure your own message types don't clash  
  // whith the ones defined in this file. ROOT reserves all message ids   
  // between 0 - 1000. User defined messages should be in the range       
  // 1001 - 10000. Sub-messages must always be in the range 1-255.        
  // To use MK_MSG() just cast your message id's to an EWidgetMessageType.

  
  int test1 = 0, test2 = 0;

  test1 = GET_MSG(msg);
  test2 = GET_SUBMSG(msg);
  
  std::cout<<msg <<"  "<< parm1<<"  "<<parm2<<std::endl;
  std::cout<<test1<<"  "<<test2<<std::endl;

  switch(test1)
    {
    case kC_COMMAND:
      switch (test2)
	{
	case kCM_MENU://TGMenuBar TGPopupMenu
	  // menu id,user data
	  // Selecting a menu item will generate the event
	  
	  break;

	  //================================================

	case kCM_MENUSELECT:
	  
	  break;

	  //================================================

	case kCM_BUTTON://TGTextButton TGPictureButton
	  // button id,user data
	  // Selecting a text or picture button will generate the event
	  switch(parm1)
	    {
	    case CONNECTBUTTON:
	      char dev[32];
	      sprintf(dev,"/dev/ttyUSB%d",connectStyle->GetSelected());

	      fd = OpenDev(dev);
	      if(fd == -1)
		{
		  StateMsg->SetText("Can't Open Serial Port");

		}
	      else
		{
		  fcntl(fd, F_SETFL, FNDELAY);// 使read函数立即返回而不阻塞。FNDELAY选项使read函数在串口无字符时立即返回且为0。
  
		  set_speed(fd,9600);
  
		  if (set_Parity(fd,8,1,'N') == -1)
		    {
		      StateMsg->SetText("Set Parity Error ...");
		    }
		  else
		    {
		      StateMsg->SetText("Open Serial Port");
		      connectButton->SetEnabled(0);
		      DeleteButton->SetEnabled(1);
		    }
		}
	      break;

	    case DELETEBUTTON:
	      // TODO
	      connectButton->SetEnabled(1);
	      DeleteButton->SetEnabled(0);
	      StateMsg->SetText("Please enter Connect");

	      break;

	    }
	  
	  break;

	  //================================================

	case kCM_CHECKBUTTON://TGCheckButton
	  // button id,user data
	  // Selecting a check button will generate the event
	  
	  break;

	  //================================================

	case kCM_RADIOBUTTON://TGRadioButton
	  // button id,user data
	  // Selecting a radio button will generate the event
	  
	  break;

	  //================================================

	case kCM_LISTBOX://TGListBox
	  // listbox id,item id
	  // Selecting an item in the listbox will generate the event
	  
	  break;

	  //================================================

	case kCM_COMBOBOX://TGComboBox
	  // combobox id,item id
	  // Selecting an item in the combobox will generate the event

	  
	  break;

	  //================================================

	case kCM_TAB://TGTab
	  // tab id,0
	  // Clicking on a tab will bring the associated composite frame to the   
	  // front and generate the event
	  
	  break;

	  //================================================
   
	default:
	  break;
	}

      break;
      
      //------------------------------------------------------------------------
      
    case kC_HSCROLL:
      switch (test2)
	{
	case kSB_LINEUP:
	  	  
	  break;

	  //================================================

	case kSB_LINEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_PAGEUP:
	  	  
	  break;

	  //================================================

	case kSB_PAGEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_SLIDERTRACK://TGHScrollBar
	  // position,0
	  // The TGHScrollBar will generate the event messages
	  
	  break;

	  //================================================

	case kSB_SLIDERPOS://TGHScrollBar
	  // position,0
	  // The TGHScrollBar will generate the event messages
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_VSCROLL:
      switch (test2)
	{
	case kSB_LINEUP:
	  	  
	  break;

	  //================================================

	case kSB_LINEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_PAGEUP:
	  	  
	  break;

	  //================================================

	case kSB_PAGEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_SLIDERTRACK://TGVScrollBar
	  // position,0
	  // The TGVScrollBar will generate the event messages
	  
	  break;

	  //================================================

	case kSB_SLIDERPOS://TGVScrollBar
	  // position,0
	  // The TGVScrollBar will generate the event messages
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_TEXTENTRY:
      switch (test2)
	{
	case kTE_TEXTCHANGED://TGTextEntry
	  // widget id,0
	  // Changing text in the text entry widget will generate the event
	  
	  break;
	  
	  //================================================
   
	case kTE_ENTER://TGTextEntry
	  // widget id,0
	  // Hitting the enter key will generate
	  
	  break;
	  
	  //================================================
   
	case kTE_TAB://TGTextEntry
	  // widget id,0
	  // Hitting the tab key will generate
	  
	  break;
	  
	  //================================================
   
	case kTE_KEY:
	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------

    case kC_CONTAINER:
      switch (test2)
	{
	case kCT_ITEMCLICK://TGListView
	  // which button, location(y<<16|x)
	  // A list view can generate the events
	  
	  break;

	  //================================================
   
	case kCT_ITEMDBLCLICK://TGListView
	  // which button, location(y<<16|x)
	  // A list view can generate the events
	  
	  break;

	  //================================================
   
	case kCT_SELCHANGED://TGListView
	  // total items,selected items
	  // A list view can generate the events
	  
	  break;

	  //================================================
   
	case kCT_KEY:
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}
	  
      break;

      //------------------------------------------------------------------------

    case kC_HSLIDER:
      switch (test2)
	{
	  // Use the functions GetMinPosition(), GetMaxPosition() and             
	  // GetPosition() to retrieve the position of the slider.

	  // Use the function GetPointerPosition() to retrieve the position of    
	  // the pointer
	  
	case kSL_POS://TGDoubleHSlider TGTripleHSlider
	  // slider id,0
	  // Dragging the slider will generate the event
	  
	  break;

	  //================================================
   
	case kSL_TRACK:
	  	  
	  break;

	  //================================================
   
	case kSL_PRESS://TGDoubleHSlider TGTripleHSlider
	  // slider id,0
	  // Pressing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_RELEASE://TGDoubleHSlider TGTripleHSlider
	  // slider id,0
	  // Releasing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_POINTER://TGTripleHSlider
	  // slider id,0
	  // Moving the pointer will generate the event
	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
	    
      break;

      //------------------------------------------------------------------------
      
    case kC_VSLIDER:
      switch (test2)
	{
	  // Use the functions GetMinPosition(), GetMaxPosition() and             
	  // GetPosition() to retrieve the position of the slider.

	  // Use the function GetPointerPosition() to retrieve the position of    
	  // the pointer
	  
	case kSL_POS://TGDoubleVSlider TGTripleHSlider
	  // slider id,0
	  // Dragging the slider will generate the event
	  
	  break;

	  //================================================
   
	case kSL_TRACK:
	  	  
	  break;

	  //================================================
   
	case kSL_PRESS://TGDoubleVSlider TGTripleHSlider
	  // slider id,0
	  // Pressing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_RELEASE://TGDoubleVSlider TGTripleHSlider
	  // slider id,0
	  // Releasing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_POINTER://TGTripleHSlider
	  // slider id,0
	  // Moving the pointer will generate the event
	  
	  break;

	  //================================================
   
	default:
	  break;  
	}

      break;

      //------------------------------------------------------------------------
      
    case kC_LISTTREE://
      switch (test2)
	{
	case kCT_ITEMCLICK://TGListTree
	  // which button, location(y<<16|x)
	  // A list tree can generate the events
	  
	  break;

	  //================================================
   
	case kCT_ITEMDBLCLICK://TGListTree
	  // which button, location(y<<16|x)
	  // A list tree can generate the events
	  
	  break;

	  //================================================
   
	case kCT_SELCHANGED:
	  
	  break;

	  //================================================
   
	case kCT_KEY:
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}            

      break;

      //------------------------------------------------------------------------
      
    case kC_TEXTVIEW:
      switch (test2)
	{
	case kTXT_ISMARKED:// TGView
	  // widget id, [true|false]  	  
	  break;

	  //================================================
   
	case kTXT_DATACHANGE:// TGView
	  // widget id, 0
	  
	  break;

	  //================================================
   
	case kTXT_CLICK2:// TGView
	  // widget id, position (y << 16) | x)
	  
	  break;

	  //================================================
   
	case kTXT_CLICK3:// TGView
	  // widget id, position (y << 16) | x)
	  
	  break;

	  //================================================
   
	case kTXT_F3:// TGView
	  // widget id, true
	  
	  break;

	  //================================================
   
	case kTXT_OPEN:
	  	  	  
	  break;

	  //================================================
   
	case kTXT_CLOSE:
	  	  	  
	  break;

	  //================================================
   
	case kTXT_SAVE:
   	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_COLORSEL:
      switch (test2)
	{ 
	case kCOL_CLICK:// TGColorPalette TGColorPick
	  // widget id,0
	  // and the signal:  ColorSelected(Pixel_t color) 

	  
	  break;

	  //================================================
   
	case kCOL_SELCHANGED:// TGColorSelect
	  // widget id,pixel
	  // and the signal: ColorSelected(Pixel_t pixel)
	  
	  // The TGColorSelect widget is like a checkbutton but instead of the    
	  // check mark there is color area with a little down arrow. When        
	  // clicked on the arrow the TGColorPopup pops up. 

	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_PATTERNSEL:
      switch (test2)
	{             
	case kPAT_CLICK:
	  	  
	  break;

	  //================================================
   
	case kPAT_SELCHANGED:
	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_MARKERSEL:
      switch (test2)
	{             
	case kMAR_CLICK:
	  	  	  
	  break;

	  //================================================
   
	case kMAR_SELCHANGED:
	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}            

      break;

      //------------------------------------------------------------------------
      
    case kC_POPUP:
      switch (test2)
	{             
	case kPOP_HIDE:
	  	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}            

      break;

      //------------------------------------------------------------------------
      
    case kC_DOCK:
      switch (test2)
	{             
	case kDOCK_DOCK:
	  	  	  	  	  
	  break;

	  //================================================
   
	case kDOCK_UNDOCK:
	  	  	  	  	  
	  break;

	  //================================================
   
	case kDOCK_SHOW:
	  	  	  	  	  
	  break;

	  //================================================
   
	case kDOCK_HIDE:
	  	  	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}      

      break;

      //------------------------------------------------------------------------
      
    case kC_MDI:
      switch (test2)
	{             
	case kMDI_CURRENT:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_CREATE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_CLOSE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_RESTORE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MOVE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_SIZE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MINIMIZE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MAXIMIZE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_HELP:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MENU:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}

      break;

      //------------------------------------------------------------------------

    default:
      break;
    }
  
  return kTRUE;
}


// 
// MainFrame.cc ends here
