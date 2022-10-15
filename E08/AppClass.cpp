#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Mackenzie Strobeck - mrs8402@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//allocate the primitive
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateTorus(3.0f, 2.0f, 6, 6, C_RED);

	//allocate the primitive
	m_pMesh2 = new MyMesh();
	m_pMesh2->GenerateTorus(3.0f, 2.0f, 8, 8, C_GREEN);

	m_pMesh3 = new MyMesh();
	m_pMesh3->GenerateCone(0.5f, 1.0f, 6, C_BLUE);

	//create a new camera
	m_pCamera = new MyCamera();

	//projection used
	m_uProjection = 1;
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//calculate view and projection
	switch (m_uProjection)
	{
	default:
	case 1:
		m_pCamera->ResetCamera();
		break;
	case 2:
		m_pCamera->ResetCamera();
		//if true we see the default in scene 1, setting false seems to centerize focus and create what the rubric wants
		m_pCamera->SetPerspective(false);
		break;
	case 3:
		m_pCamera->ResetCamera();
		
		//false position gives scene 2, true gives scene 1, must use an axis value of some type
		//axis_z works more for setup than set position; axis_x is needed but on own zoomed in on red object! axis_y is more height based
		// adding to axis_x gives a tilted view point away from front, subtracting tilts away from back, multiplying is best bet for easiest solution
		m_pCamera->SetPosition(30.0f * AXIS_X); //using 30.0f gives exact location just about
		//10.0f too close to camera, 20.0f getting closer to solution

		// 1.0f and just axis_z gives upside down results compared to rubric, multiple of -1.0f checks out
		//setup uses a vec3 to determine up or down in camera world; since 1.0f means down, neg must mean up
		m_pCamera->SetUp(-1.0f * AXIS_Z);
		break;
	case 4:
		m_pCamera->ResetCamera();

		//based on case 3, z axis is probably best answer, y wouldn't look right; just z axis looks like blue cone and green circle, where is the red??
		//subtraction makes the camera point to right side leading to the shapes facing top left corner, addition makes similiar look but to right
		//-10.f needs to zoom in more on green and red
		m_pCamera->SetPosition(-20.0f * AXIS_Z);
		//XZ def not right but interesting perspective
		//m_pCamera->SetPosition(-20.0f * AXIS_XZ);
		break;
	case 5:
		m_pCamera->ResetCamera();

		//same as case 4 but no cone in it, so alter same function?
		//10.0f results in clipping, 15 clipping, 20 seems okay
		m_pCamera->SetPosition(-25.0f * AXIS_Z);

		//need to set distance closer so it cuts out the cone from frame. Use maybe SetNearFar?
		//can apply vec2 values and get more direct solution from near far; x, y
		m_pCamera->SetNearFar(vector2(18.0f, 100.0f));
		break;
	case 6:
		m_pCamera->ResetCamera();

		//same as 5 but just green ring
		//25 too far, 10 too close
		m_pCamera->SetPosition(-15.0f * AXIS_Z);

		//using the same nearfar as case 5 just motified
		//5 was close, but needs smaller value; 1 works for the most part and need to alter value on end; 5 is too close, 10 works
		m_pCamera->SetNearFar(vector2(1.0f, 10.0f));
		break;
	case 7:
		m_pCamera->ResetCamera();

		//upside down means using y axis! need to pay attention to pos and neg values
		// using position setting did not work properly, attempt setup such as in case 3
		//m_pCamera->SetPosition(-20.0f * AXIS_Z); ,--> using this makes the colors reverse
		
		//pos is up, need to use neg
		//basically recreates default scene but with upside down cone. Needs red on outside, green in middle, blue far back
		m_pCamera->SetUp(-1.0f * AXIS_Y);

		//10 is way too close and clips, 7 too little
		m_pCamera->SetNearFar(vector2(9.5f, 100.0f));
		break;
	}

	m_pCamera->CalculateProjectionMatrix();
	m_pCamera->CalculateViewMatrix();

	matrix4 m4Projection = m_pCamera->GetProjectionMatrix();
	matrix4 m4View = m_pCamera->GetViewMatrix();


	//draw the primitive
	m_pMesh1->Render(m4Projection, m4View, glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X));
	m_pMesh2->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, -5.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X));
	m_pMesh3->Render(m4Projection, m4View, glm::translate(vector3(0.0f, 0.0f, -10.0f)));

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}