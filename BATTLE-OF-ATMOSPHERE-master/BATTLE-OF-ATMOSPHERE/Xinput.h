/**
* @file KamikuboXinputLib.h
* @brief XinputのLib
*/
#ifndef XINPUT_H
#define XINPUT_H

#include<Windows.h>
#include<Xinput.h>

	/**
	* @enum CTRL
	* @brief このLibで対応しているXboxコントローラーのボタン一覧
	*/
enum class CTRL
{
	BUTTON_A = 0x5800,		//! Aボタン
	BUTTON_B = 0x5801,		//! Bボタン
	BUTTON_X = 0x5802,		//! Xボタン
	BUTTON_Y = 0x5803,		//! Yボタン

	RSHOULDER = 0x5804,		//! RBボタン
	LSHOULDER = 0x5805,		//! LBボタン

	TRIGGER_LEFT = 0x5806,	//! 左トリガー
	TRIGGER_RIGHT = 0x5807,	//! 右トリガー

	PAD_UP = 0x5810,		//! 方向パッド上
	PAD_DOWN = 0x5811,		//! 方向パッド下
	PAD_LEFT = 0x5812,		//! 方向パッド左
	PAD_RIGHT = 0x5813,		//! 方向パッド右

	LTHUMB_PRESS = 0x5816,	//! 左スティック押込み
	RTHUMB_PRESS = 0x5817,	//! 右スティック押込み

	LTHUMB_UP = 0x5820,		//! 左スティック上
	LTHUMB_DOWN = 0x5821,	//! 左スティック下
	LTHUMB_RIGHT = 0x5822,	//! 左スティック右
	LTHUMB_LEFT = 0x5823,	//! 左スティック左

	RTHUMB_UP = 0x5830,		//! 右スティック上
	RTHUMB_DOWN = 0x5831,	//! 右スティック下
	RTHUMB_RIGHT = 0x5832,	//! 右スティック右
	RTHUMB_LEFT = 0x5833,	//! 右スティック左

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
	* @brief Xinputを使用するためのクラス
	* @note 現在は１つしかインスタンス生成できないが、最大４つ生成できるようにする予定
	*/
	class Xinput
	{
	public:

		/**
		* @brief インスタンスを生成する
		* @param num インスタンスを生成する数
		* @note ４つまでしか生成できない
		*/
		static void Create(int num = 1);

		/**
		* @brief Xinputのインスタンスをゲットする
		* @param num プレイヤーの番号
		* @return 引数によって指定したインスタンス
		*/
		static Xinput* GetInstance(Player num);

		/**
		* @brief インスタンスを破棄
		*/
		static void Destroy();

		/**
		* @brief スティックのデットゾーンを変更する関数
		* @param left 左スティックのデットゾーン
		* @param right 右スティックのデットゾーン
		* @note この関数を呼び出さなくとも左スティックに7849、右スティックに8689が設定されている
		*/
		void InitThumbDeadzone(int left, int right);

		/**
		* @brief トリガーのデットゾーンを変更する関数
		* @param left 左トリガーのデットゾーン
		* @param right 右トリガーのデットゾーン
		* @note この関数を呼び出さなくとも両トリガーに30が設定されている
		*/
		void InitTriggerDeadzone(int left, int right);

		/**
		* @brief コントローラーの入力状態を更新する関数
		*/
		void UpdateController();

		/**
		* @brief コントローラーの入力状態を更新する関数。接続されていない場合接続されるまでループし続ける。
		*/
		void UpdateControllerEx();

		/**
		* @brief 入力され続けられているかどうかを返す関数
		* @param key 確認したいキー
		* @return 指定したキーが入力されているならtrue、入力されていないならfalseを返す
		*/
		bool IsKeyStrokePressed(CTRL key);

		/**
		* @brief 入力した瞬間かどうかを返す関数
		* @param key 確認したいキー
		* @return 指定したキーが入力された瞬間ならtrue、入力された瞬間でないならfalseを返す
		*/
		bool IsKeyStrokePushed(CTRL key);

		/**
		* @brief 放された瞬間かどうかを返す関数
		* @param key 確認したいキー
		* @return 指定したキーが放された瞬間ならtrue、放された瞬間でないならfalseを返す
		*/
		bool IsKeyStrokeReleased(CTRL key);

		/**
		* @brief コントローラーをバイブレーションさせる関数
		* @param left_value 左モーターの強さ。最大65535
		* @param right_value 右モーターの強さ。最大65535
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
