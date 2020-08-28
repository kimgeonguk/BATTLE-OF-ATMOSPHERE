#include"Xinput.h"

	Xinput* Xinput::instance[] = { NULL };

	Xinput::Xinput()
	{
		ZeroMemory(&XinputState, sizeof(XINPUT_STATE));
	}

	Xinput::~Xinput()
	{
	}

	void Xinput::Create(int num)
	{
		if (num > (int)Player::MAX)num = (int)Player::MAX;

		for (int i = 0; i < num; i++)
		{
			if (instance[i] == NULL)
			{
				instance[i] = new Xinput();
				instance[i]->player_num = (Player)i;
			}
		}
	}

	Xinput* Xinput::GetInstance(Player num)
	{
		if (instance[(int)num] != NULL)
		return instance[(int)num];
	}

	void Xinput::Destroy()
	{
		for (int i = 0; i < (int)Player::MAX; i++)
		{
			delete instance[i];
			instance[i] = NULL;
		}
	}

	void Xinput::UpdateController()
	{
		XInputGetState((int)player_num, &XinputState);
		XInputGetKeystroke((int)player_num, NULL, &XinputKeyStroke);
	}

	void Xinput::UpdateControllerEx()
	{
		while (true)
		{
			XInputGetKeystroke((int)player_num, NULL, &XinputKeyStroke);
			if (XInputGetState((int)player_num, &XinputState) == ERROR_SUCCESS)
				break;
		}
	}

	void Xinput::InitThumbDeadzone(int left, int right)
	{
		m_left_deadzone = left;
		m_right_deadzone = right;
	}

	void Xinput::InitTriggerDeadzone(int left, int right)
	{
		m_left_threshold = left;
		m_right_threshold = right;
	}

	bool Xinput::IsKeyStrokePressed(CTRL key)
	{
		switch (key)
		{
		case CTRL::BUTTON_A:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
				return true;
			return false;
		case CTRL::BUTTON_B:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
				return true;
			return false;
		case CTRL::BUTTON_X:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
				return true;
			return false;
		case CTRL::BUTTON_Y:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				return true;
			return false;

		case CTRL::RSHOULDER:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				return true;
			return false;
		case CTRL::LSHOULDER:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				return true;
			return false;

		case CTRL::TRIGGER_LEFT:
			if (XinputState.Gamepad.bLeftTrigger > m_left_threshold)
				return true;
			return false;
		case CTRL::TRIGGER_RIGHT:
			if (XinputState.Gamepad.bRightTrigger > m_right_threshold)
				return true;
			return false;

		case CTRL::PAD_UP:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				return true;
			return false;
		case CTRL::PAD_DOWN:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				return true;
			return false;
		case CTRL::PAD_LEFT:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				return true;
			return false;
		case CTRL::PAD_RIGHT:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				return true;
			return false;

		case CTRL::LTHUMB_PRESS:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
				return true;
			return false;
		case CTRL::RTHUMB_PRESS:
			if (XinputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				return true;
			return false;

		case CTRL::LTHUMB_UP:
			if (XinputState.Gamepad.sThumbLY >= m_left_deadzone)
				return true;
			return false;
		case CTRL::LTHUMB_DOWN:
			if (XinputState.Gamepad.sThumbLY <= -m_left_deadzone)
				return true;
			return false;
		case CTRL::LTHUMB_RIGHT:
			if (XinputState.Gamepad.sThumbLX >= m_left_deadzone)
				return true;
			return false;
		case CTRL::LTHUMB_LEFT:
			if (XinputState.Gamepad.sThumbLX <= -m_left_deadzone)
				return true;
			return false;
		case CTRL::RTHUMB_UP:
			if (XinputState.Gamepad.sThumbRY >= m_right_deadzone)
				return true;
			return false;
		case CTRL::RTHUMB_DOWN:
			if (XinputState.Gamepad.sThumbRY <= -m_right_deadzone)
				return true;
			return false;
		case CTRL::RTHUMB_RIGHT:
			if (XinputState.Gamepad.sThumbRX >= m_right_deadzone)
				return true;
			return false;
		case CTRL::RTHUMB_LEFT:
			if (XinputState.Gamepad.sThumbRY <= -m_right_deadzone)
				return true;
			return false;
		default:
			break;
		}

		return false;
	}

	bool Xinput::IsKeyStrokePushed(CTRL key)
	{
		return((XinputKeyStroke.VirtualKey == (WORD)key) & (XinputKeyStroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)) ? true : false;
	}

	bool Xinput::IsKeyStrokeReleased(CTRL key)
	{
		return ((XinputKeyStroke.VirtualKey == (WORD)key) & (XinputKeyStroke.Flags == XINPUT_KEYSTROKE_KEYUP)) ? true : false;
	}

	void Xinput::RunVibration(int left_value, int right_value)
	{
		//	バイブレーションの強さ
		XINPUT_VIBRATION Vibration;
		ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
		if (left_value > MAX_VIBRATION_VALUE) left_value = MAX_VIBRATION_VALUE;
		if (right_value > MAX_VIBRATION_VALUE)right_value = MAX_VIBRATION_VALUE;

		Vibration.wLeftMotorSpeed = left_value;
		Vibration.wRightMotorSpeed = right_value;

		XInputSetState((int)player_num, &Vibration);
	}
