#include "TutorialApp.h"
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>



using namespace Urho3D;

TutorialApp::TutorialApp(Context* context):
    Application(context),
    yaw_(0.0f),
    pitch_(0.0f)
{

}

void TutorialApp::Setup()
{
    engineParameters_["WindowResizable"] = true;
    engineParameters_["FullScreen"] = false;
}

void TutorialApp::Start()
{
    CreateScene();
    SubscribeToEvents();
}

void TutorialApp::Stop()
{

}

void TutorialApp::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
   using namespace KeyDown;

    // Check for pressing ESC. Note the engine_ member variable for convenience access to the Engine object
    int key = eventData[P_KEY].GetInt();

    if (key == KEY_ESCAPE)
    {
        engine_->Exit();
    }

}

void TutorialApp::CreateScene()
{
    scene_ = new Scene(context_);

    //Create the Octree
    scene_->CreateComponent<Octree>();

    //Get the Resource Cache subsystem
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    //Create Model
    Node* boxNode = scene_->CreateChild("Model Node");
    StaticModel* boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));


    //Create Light
    Node* lightNode = scene_->CreateChild("Light Node");
    lightNode->SetDirection( Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);

    //Create Camera
    cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->Translate(Vector3(0,0,-2));
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(100.0f);


    //Create and Setup Viewport
    Renderer* renderer = GetSubsystem<Renderer>();

    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
    renderer->SetViewport(0, viewport);

}

void TutorialApp::SubscribeToEvents()
{

    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(TutorialApp, HandleKeyDown));
    SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(TutorialApp, HandleMouseMoved));
}

void TutorialApp::HandleMouseMoved(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;

    int dx = eventData[P_DX].GetInt();
    int dy = eventData[P_DY].GetInt();

    pitch_ += dy * 0.01f;
    pitch_ = Clamp(pitch_,-90.0f,90.0f);

    yaw_ += dx * 0.03f;

    cameraNode_->SetRotation(Quaternion(pitch_,yaw_,0.0f));
}



URHO3D_DEFINE_APPLICATION_MAIN(TutorialApp)
