#include "..\include\CGameStateIntro.h"

CGameStateIntro::CGameStateIntro(void){
}

CGameStateIntro::~CGameStateIntro(void)
{
	m_TE.clear();
}

void CGameStateIntro::Initialize(){
}

void CGameStateIntro::Activate(CGameData &data, CConfigData &cfg, CGraphics &con){
  //CLog *pLog = CLog::Instance();

  //pyro setup
  //**********************
  //m_effect.Init(con.m_d3ddev);
  //m_effect.LoadFile(cfg.EffectsFileI);//"assets\\data\\effects_i.dat");
  //m_effectNumber = 0;
  //m_effectMax = m_effect.GetNumberEffects();
  //pLog->Log("******* Number of Intro Screen effects loaded", m_effectMax);
}

CGameStateObject* CGameStateIntro::Update(double timeDifference,  CGameData &data, CConfigData &cfg, CGraphics &con){
  m_event = EVENT_GO_NO_WHERE;
  m_mouse.SetHandle(data.m_hWnd);//needed for mouse

  //static double counterTime = 0;
  //counterTime += timeDifference;
  //con.m_textureRed = 155;//data.m_textureColorRed;
  //con.m_textureGreen = 155;//data.m_textureColorGreen;
  //con.m_textureBlue = 155;//data.m_textureColorBlue;

  /*
  CAudioManager *pAudio = CAudioManager::Instance();
  if(cfg.PlayMusic == true && pAudio->IsPlaying(0) == false)
    pAudio->PlayAudioClip(0, 1);
  */

  //left click to continue
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< bypassed
  if(::GetActiveWindow() == data.m_hWnd && data.m_bLeftMouseDown)
    m_event = EVENT_GO_MAIN;
  //m_effect.Update(m_startTime);

  for(unsigned int i=0; i< m_TE.size(); i++){
    if (m_TE[i].event == m_event){
      return m_TE[i].p_gso;
    }
  }
  return 0;
}

void CGameStateIntro::Render(CGraphics &con, CGameData &data, CConfigData &cfg){
  ::ShowCursor(false);
  CLog *pLog = CLog::Instance();
  static bool bLostDevice = false;

  //test to see if graphic device is lost, if so, deal with it
  //**********************************************************
  HRESULT hr;
  if(FAILED(hr = con.m_d3ddev->TestCooperativeLevel())){
    
    //device is lost...cannot be reset...exit Render() function
    if(hr == D3DERR_DEVICELOST){
      if(bLostDevice == false){
        bLostDevice = true;
        con.DeleteLost();    //delete one time per failure
        //m_effect.Delete();
        //pLog->Log("Deleted");
      }
      return;
    }

    //device was lost...but now can be RESET
    else if( hr == D3DERR_DEVICENOTRESET ){
      hr = con.m_d3ddev->Reset(&con.GetDPP());      
      if(SUCCEEDED(hr)){
        //m_effect.Init(con.m_d3ddev);
        //m_effect.LoadFile(cfg.EffectsFileI);
        //m_effectNumber = 0;
        //m_effectMax = m_effect.GetNumberEffects();
        //pLog->Log("******* Number of effects reloaded", m_effectMax);
        con.LoadAssetFile(cfg.GamePlayAssetFile);
        con.LoadAssetFile(cfg.FrameworkAssetFile);     
        con.ReloadLost();
        bLostDevice = false;
      }
      return;
    }
  }

  // clear the window to a deep blue
  con.m_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);//   0, 111, 255), 1.0f, 0);
  con.m_d3ddev->BeginScene();    // begins the 3D scene

  GRAPHIC_IMAGE gi;  
  con.BeginRender();
  gi = con.GetSprite(1002);
  gi.scale = 4.5;
  con.RenderSprite(gi, 0, 0, 255, 255, 255);
  
  con.EndRender();

  m_effect.Render(); 

  con.DrawRect(0, 0, 599, 449, 255, 0, 0);
  con.DrawRect(601, 0, 1023, 449, 255, 0, 0);
  con.DrawRect(0, 451, 1023, 766, 255, 0, 0);

  //mouse cursor
  con.DrawCircle(m_mouse.MouseX(), m_mouse.MouseY(), 255, 255, 255, 10);

  //*********************************************
  //test of vector
  /*
  std::vector<float> vecNum;
  for(int i = 0; i < 50; ++i)
    vecNum.push_back(3.14159345f);
  con.PrintVector(vecNum, F_V12, 5, 5, 0, 0, 0, 255);
  */
  //*********************************************

  //*********************************************
  //THIS IS MORE EFFICIENT THAN
  //con.PrintTest("FPS", data.m_FPS, F_A12, 10, 10, 0, 0, 0, 255);

  //THIS.....................
  /*
  for(int i = 0; i < 50;++i){
    for(int j = 0; j < 10; ++j){
      con.Print("FPS", data.m_FPS, F_A12, 10 + (j * 100), 10 + (i * 15), i * 5, i * 5, i * 5, 255);
    }  
  }
  */
  //*********************************************

  con.Print("Introduction - Click to continue",F_A8, 420, 750, 255, 255, 0, 255);

  //con.Print("
  if(cfg.DisplayDebugInfo == true){
    con.Print("FPS", data.m_FPS, F_A12, 500, 680, 255, 255, 0, 255);
    con.Print("Mouse X", m_mouse.MouseX(), F_V12, 510, 330, 255, 255, 255, 255);
    con.Print("Mouse Y", m_mouse.MouseY(), F_V12, 510, 350, 255, 255, 255, 255);
    

  }

  con.m_d3ddev->EndScene();    // ends the 3D scene
  hr = con.m_d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
 
  return;
}

void CGameStateIntro::ProcessEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
}

void CGameStateIntro::Deactivate(CGameData &data, CConfigData &cfg, CGraphics &con){
}
void CGameStateIntro::Resume(){
}
void CGameStateIntro::Pause(){
}
void CGameStateIntro::Save(){
}

void CGameStateIntro::AddTransitionEvent(int event, CGameStateObject* p_Next){
  TRANSITION_EVENT te;
  te.event=event;
  te.p_gso = p_Next;

  m_TE.push_back(te);
}