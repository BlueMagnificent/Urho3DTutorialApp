#ifndef __TUTORIALAPP_H_
#define __TUTORIALAPP_H_

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

class TutorialApp : public Application
{
    URHO3D_OBJECT(TutorialApp, Application)

public:
    TutorialApp(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    void HandleMouseMoved(StringHash eventType, VariantMap& eventData);

private:
    void CreateScene();
    void SubscribeToEvents();

    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;

    /// Camera yaw angle.
    float yaw_;
    /// Camera pitch angle.
    float pitch_;
};

#endif // #ifndef __TUTORIALAPP_H_
