/**
* @file KamikuboXinputLib.h
* @brief Xinput��Lib
*/
#ifndef XINPUT_H
#define XINPUT_H

#include<Windows.h>
#include<Xinput.h>

	/**
	* @enum CTRL
	* @brief ����Lib�őΉ����Ă���Xbox�R���g���[���[�̃{�^���ꗗ
	*/
enum class CTRL
{
	BUTTON_A = 0x5800,		//! A�{�^��
	BUTTON_B = 0x5801,		//! B�{�^��
	BUTTON_X = 0x5802,		//! X�{�^��
	BUTTON_Y = 0x5803,		//! Y�{�^��

	RSHOULDER = 0x5804,		//! RB�{�^��
	LSHOULDER = 0x5805,		//! LB�{�^��

	TRIGGER_LEFT = 0x5806,	//! ���g���K�[
	TRIGGER_RIGHT = 0x5807,	//! �E�g���K�[

	PAD_UP = 0x5810,		//! �����p�b�h��
	PAD_DOWN = 0x5811,		//! �����p�b�h��
	PAD_LEFT = 0x5812,		//! �����p�b�h��
	PAD_RIGHT = 0x5813,		//! �����p�b�h�E

	LTHUMB_PRESS = 0x5816,	//! ���X�e�B�b�N������
	RTHUMB_PRESS = 0x5817,	//! �E�X�e�B�b�N������

	LTHUMB_UP = 0x5820,		//! ���X�e�B�b�N��
	LTHUMB_DOWN = 0x5821,	//! ���X�e�B�b�N��
	LTHUMB_RIGHT = 0x5822,	//! ���X�e�B�b�N�E
	LTHUMB_LEFT = 0x5823,	//! ���X�e�B�b�N��

	RTHUMB_UP = 0x5830,		//! �E�X�e�B�b�N��
	RTHUMB_DOWN = 0x5831,	//! �E�X�e�B�b�N��
	RTHUMB_RIGHT = 0x5832,	//! �E�X�e�B�b�N�E
	RTHUMB_LEFT = 0x5833,	//! �E�X�e�B�b�N��

};

	/**
	* @enum Player
	*/
enum class Player
{
	ONE,
	TWO,
	THREE,
	FOUR,
	MAX,
};

	/**
	* @brief Xinput���g�p���邽�߂̃N���X
	* @note ���݂͂P�����C���X�^���X�����ł��Ȃ����A�ő�S�����ł���悤�ɂ���\��
	*/
	class Xinput
	{
	public:

		/**
		* @brief �C���X�^���X�𐶐�����
		* @param num �C���X�^���X�𐶐����鐔
		* @note �S�܂ł��������ł��Ȃ�
		*/
		static void Create(int num = 1);

		/**
		* @brief Xinput�̃C���X�^���X���Q�b�g����
		* @param num �v���C���[�̔ԍ�
		* @return �����ɂ���Ďw�肵���C���X�^���X
		*/
		static Xinput* GetInstance(Player num);

		/**
		* @brief �C���X�^���X��j��
		*/
		static void Destroy();

		/**
		* @brief �X�e�B�b�N�̃f�b�g�]�[����ύX����֐�
		* @param left ���X�e�B�b�N�̃f�b�g�]�[��
		* @param right �E�X�e�B�b�N�̃f�b�g�]�[��
		* @note ���̊֐����Ăяo���Ȃ��Ƃ����X�e�B�b�N��7849�A�E�X�e�B�b�N��8689���ݒ肳��Ă���
		*/
		void InitThumbDeadzone(int left, int right);

		/**
		* @brief �g���K�[�̃f�b�g�]�[����ύX����֐�
		* @param left ���g���K�[�̃f�b�g�]�[��
		* @param right �E�g���K�[�̃f�b�g�]�[��
		* @note ���̊֐����Ăяo���Ȃ��Ƃ����g���K�[��30���ݒ肳��Ă���
		*/
		void InitTriggerDeadzone(int left, int right);

		/**
		* @brief �R���g���[���[�̓��͏�Ԃ��X�V����֐�
		*/
		void UpdateController();

		/**
		* @brief �R���g���[���[�̓��͏�Ԃ��X�V����֐��B�ڑ�����Ă��Ȃ��ꍇ�ڑ������܂Ń��[�v��������B
		*/
		void UpdateControllerEx();

		/**
		* @brief ���͂��ꑱ�����Ă��邩�ǂ�����Ԃ��֐�
		* @param key �m�F�������L�[
		* @return �w�肵���L�[�����͂���Ă���Ȃ�true�A���͂���Ă��Ȃ��Ȃ�false��Ԃ�
		*/
		bool IsKeyStrokePressed(CTRL key);

		/**
		* @brief ���͂����u�Ԃ��ǂ�����Ԃ��֐�
		* @param key �m�F�������L�[
		* @return �w�肵���L�[�����͂��ꂽ�u�ԂȂ�true�A���͂��ꂽ�u�ԂłȂ��Ȃ�false��Ԃ�
		*/
		bool IsKeyStrokePushed(CTRL key);

		/**
		* @brief �����ꂽ�u�Ԃ��ǂ�����Ԃ��֐�
		* @param key �m�F�������L�[
		* @return �w�肵���L�[�������ꂽ�u�ԂȂ�true�A�����ꂽ�u�ԂłȂ��Ȃ�false��Ԃ�
		*/
		bool IsKeyStrokeReleased(CTRL key);

		/**
		* @brief �R���g���[���[���o�C�u���[�V����������֐�
		* @param left_value �����[�^�[�̋����B�ő�65535
		* @param right_value �E���[�^�[�̋����B�ő�65535
		*/
		void RunVibration(int left_value = 65535, int right_value = 65535);

	private:

		const int MAX_VIBRATION_VALUE = 65535;

		Player player_num;

		int m_left_deadzone = 7849;

		int m_right_deadzone = 8689;

		int m_left_threshold = 30;

		int m_right_threshold = 30;

		Xinput();

		~Xinput();

		Xinput(const Xinput&);

		Xinput& operator =(const Xinput&);

		static Xinput* instance[(int)Player::MAX];

		XINPUT_STATE XinputState;

		XINPUT_KEYSTROKE XinputKeyStroke;

	};

#endif // !KAMIKUBO_XINPUT_LIB_H_
