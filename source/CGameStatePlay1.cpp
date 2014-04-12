#include "..\include\CGameStatePlay1.h"
 
CGameStatePlay1::CGameStatePlay1(){
}

CGameStatePlay1::~CGameStatePlay1()
{
	m_TE.clear();
}

void CGameStatePlay1::Initialize(){

}

void CGameStatePlay1::Activate(CGameData &data, CConfigData &cfg, CGraphics &con){
  CLog *pLog = CLog::Instance();
  
  //pyro setup
  //**********************
  //m_effect.Init(con.m_d3ddev);
  //m_effect.LoadFile(cfg.EffectsFile);//"assets\\data\\effects.dat");
  //m_effectNumber = 0;
  //m_effectMax = m_effect.GetNumberEffects();
  //pLog->Log("******* Number of effects loaded", m_effectMax);

  //audio setup
  /*
  CAudioManager *pAudio = CAudioManager::Instance();
  if(cfg.PlayMusic == 1)
    data.m_playMusic = true;
  else
    data.m_playMusic = false;

  if(cfg.PlaySounds == 1)
    data.m_playSound = true;
  else
    data.m_playSound = false;
*/

  //play level 1
  //*****************************************************
  //if(data.m_mapLevelToPlay == 1){
  //  if(data.LoadGameLevel(cfg.Level1) == false){
  //    pLog->Log("Failed to load level file", cfg.Level1);
  //    m_bReadyToRender = false;
  //  }    
  //  else
  //    m_bReadyToRender = true;
  //}

}

void CGameStatePlay1::Deactivate(CGameData &data, CConfigData &cfg, CGraphics &con){
  //pyro housekeeping
  //********************************
  //m_effect.Delete();
}

//***************************************************************
//                         U P D A T E
//***************************************************************
CGameStateObject* CGameStatePlay1::Update(double timeDifference,  CGameData &data, CConfigData &cfg, CGraphics &con){
  m_event = EVENT_GO_NO_WHERE;
  CLog *pLog = CLog::Instance();
  CAudioManager *pAudio = CAudioManager::Instance();
  CFizzix *pFizzix = CFizzix::Instance();  
   
  if(::GetActiveWindow() != data.m_hWnd)
    return NULL;

  m_mouse.SetHandle(data.m_hWnd);//needed for mouse
  //temporarily used to allow suer control of colors...keys UIOJKL
  con.m_textureRed = data.m_textureColorRed;
  con.m_textureGreen = data.m_textureColorGreen;
  con.m_textureBlue = data.m_textureColorBlue;


  //manages time
//  timeDifference *= data.m_timeScale; //multiply by 1 or 2
  static double keyTime = 0;
  keyTime += timeDifference;
  static double effectTime = 0;
  effectTime += timeDifference;

  //******************************************************* PROCESS INPUT
  if(::GetActiveWindow() == data.m_hWnd){// && data.m_bPaused == false){
  }
    //if(data.m_bLeftMouseDown)
    if(keyDown(VK_ESCAPE) == true)
      m_event = EVENT_GO_MAIN;

    //updates User Interface
    m_UI.ResetState();
    m_UI.Update(timeDifference, m_mouse.MouseX(), m_mouse.MouseY(), data);
    m_UIstate = m_UI.GetUIState();

    //process panel selection
    //***************************************************************************    
    if(m_UIstate >= 7 && m_UIstate <= 11){  //user has clicked on 1 of 5 sprites
      //int nWeapon = m_UIstate - 6;
      //data.m_mouseState = 1;       //ready to add something on map by clicking
      //data.m_mouseValue = nWeapon; //id of weapon to add when left click happens      
    }    

    //repair defensive units
    //********************************
    //if(m_UI.GetUIState() < 1 && data.m_bRightMouseDown == true && rightClickTime  > 0.3  && data.m_bGameOver == false){
    //  rightClickTime = 0.0;

    //ESC key  - reset selection of defensive weapons
    //if(keyDown(VK_ESCAPE) == true)
    //  m_UI.ResetState();
      
      //quit map level
      //if(m_UIstate == UI_QUIT)
      //  m_event = EVENT_GO_MAIN; //CREDITS;
      //toggle grid
      //else if(keyDown('G') == true && gridTime > 0.2 && cfg.DisplayDebugInfo == true){
     // }
  
  //manage sprite animation
  /*
  GRAPHIC_IMAGE gi;
  if(data.m_bPaused == false && data.m_bGameOver == false){
    for(unsigned int i = 0; i < data.m_pObject.size(); ++i){  //iterate through all objects    
      gi = con.GetSprite(data.m_pObject[i]->m_go.m_sprite);   //load graphic image
      if(gi.frameMax > 1){                          //this is an animated sequence
        //pLog->Log(data.m_pObject[i]->m_go.m_weaponType, 
        //          data.m_pObject[i]->m_go.animTime,
        //          data.m_pObject[i]->m_go.frameCount,
        //          gi.frameMax);
        data.m_pObject[i]->m_go.animTime += timeDifference;    //update frame animation timer
        if(data.m_pObject[i]->m_go.animTime > gi.updateInterval){//time to change
          data.m_pObject[i]->m_go.animTime = 0;                  //clear timer
          data.m_pObject[i]->m_go.frameCount++;             //inc frame number
          if(data.m_pObject[i]->m_go.frameCount > gi.frameMax)
            data.m_pObject[i]->m_go.frameCount = 1;
        }
      }      
    }
  }
  */

  //********************* do if not paused
  if(data.m_bPaused == false && data.m_bGameOver == false){
  }


  //update all objects
  //************************
  /*
  if(data.m_bPaused == false){// && data.m_bGameOver == false){
    for(unsigned int i = 0; i < data.m_pObject.size(); ++i){
      if(data.m_pObject.empty() == false){
        data.m_pObject[i]->Update(timeDifference, data);
      }
    }
  }
  */

  
  //pyro updating
  //*************************
  //if(data.m_bPaused == false)  //allow for special effects if HQ is destroyed
  //  m_effect.Update(m_startTime);

  // data.m_gameClock.Update();
  if(data.m_bPaused == false && data.m_bGameOver == false)
    data.Update(timeDifference);  

  //manage game state changes
  for(unsigned int i=0; i< m_TE.size(); i++){
    if (m_TE[i].event == m_event){
      return m_TE[i].p_gso;
    }
  }
  return 0;
}

//***************************************************************
//                         R E N D E R 
//***************************************************************
void CGameStatePlay1::Render(CGraphics &con,  CGameData &data, CConfigData &cfg){
  //::ShowCursor(true);
  CLog *pLog = CLog::Instance();
  static bool bLostDevice = false; 
  
  ::SetCursor(false);

  //update sounds
  CAudioManager *pAudio = CAudioManager::Instance();
  pAudio->Update();

  //test to see if graphic device is lost, if so, deal with it
  //**********************************************************
  HRESULT hr;
  if(FAILED(hr = con.m_d3ddev->TestCooperativeLevel())){
    
    //device is lost...cannot be reset...exit Render() function
    if(hr == D3DERR_DEVICELOST){
      if(bLostDevice == false){
        bLostDevice = true;
        //pLog->Log("Lost");
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
        //pLog->Log("Loss of focus...reloading!");
        //m_effect.Init(con.m_d3ddev);
        //m_effect.LoadFile(cfg.EffectsFile);// "assets\\data\\effects.dat");
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
  con.m_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(data.m_screenColorRed, data.m_screenColorGreen, data.m_screenColorBlue), 1.0f, 0);//0, 111, 255
  con.m_d3ddev->BeginScene();  
  con.BeginRender();
  GRAPHIC_IMAGE gi;

  //render map
  //gi = con.GetSprite(data.m_mapSpriteNumber);//103
  //con.RenderSprite(gi, 0, 0, 255, 255, 255);
  //renders all game objects
  //for(int layer = 0; layer < 11; ++layer){
  //  for(unsigned int i = 0; i < data.m_pObject.size(); ++i){
  //    if(data.m_pObject[i]->GetLayer() == layer)
  //        data.m_pObject[i]->Render(con, data);
  //  }
  //}
  

  //render UI panels
  //m_UI.Render(con, data);

  //paused
  //if(data.m_bPaused == true){
  //  gi = con.GetSprite(1011);
  //  con.RenderSprite(gi, con.GetScreenCenterX() - gi.width/2, con.GetScreenCenterY() - gi.height/2, 255, 255, 255);
  //}

  con.EndRender();  
  
  //pyro rendering
  /*
        dy = cos(data.m_pObject[i]->m_go.m_angle) * data.m_pObject[i]->m_go.m_weaponRadius;
        dx = sin(data.m_pObject[i]->m_go.m_angle) * data.m_pObject[i]->m_go.m_weaponRadius;
          smokeRadius = data.m_pObject[i]->m_go.m_weaponRadius * 0.001;
          fireRadius = data.m_pObject[i]->m_go.m_weaponRadius * 0.005;
          m_effectNumber = data.m_pObject[i]->m_go.m_weaponSmoke; 
          m_effect.Add(m_effectNumber, static_cast<float>(data.m_pObject[i]->m_go.m_posX) + dx,static_cast<float>(data.m_pObject[i]->m_go.m_posY) - dy, smokeRadius);
          m_effectNumber = data.m_pObject[i]->m_go.m_weaponEffect;
          m_effect.Add(m_effectNumber, static_cast<float>(data.m_pObject[i]->m_go.m_posX) + dx,static_cast<float>(data.m_pObject[i]->m_go.m_posY) - dy, fireRadius);
  */

  //renders UI panel outlines
//  m_UI.RenderOutlines(con, data);

  
  //draw mouse
  con.DrawCircle(m_mouse.MouseX(), m_mouse.MouseY(), 255, 255, 255, 5);  
  con.DrawRect(m_mouse.MouseX() - 16, m_mouse.MouseY() - 16, m_mouse.MouseX() + 16, m_mouse.MouseY() + 16, 255, 255, 255);



  con.Print("Play State", F_V16, 450, 720, 255, 255, 255, 255);
  con.Print("Press ESC to Return to Main Menu", F_V16, 400, 50, 255, 255, 255, 255);



if(cfg.DisplayDebugInfo == true){
  con.Print("FPS", data.m_FPS, F_V16, 20, 10, 255, 255, 255, 255);
  con.Print("Mouse X", m_mouse.MouseX(), F_V16, 860, 10, 255, 255, 255, 255);
  con.Print("Mouse Y", m_mouse.MouseY(), F_V16, 860, 30, 255, 255, 255, 255);
}

  con.m_d3ddev->EndScene();    // ends the 3D scene
  hr = con.m_d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}
  
void CGameStatePlay1::ProcessEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

}



void CGameStatePlay1::Resume(){
}
void CGameStatePlay1::Pause(){
}
void CGameStatePlay1::Save(){
}

void CGameStatePlay1::AddTransitionEvent(int event, CGameStateObject* p_Next){
  TRANSITION_EVENT te;
  te.event=event;
  te.p_gso = p_Next;

  m_TE.push_back(te);
}

