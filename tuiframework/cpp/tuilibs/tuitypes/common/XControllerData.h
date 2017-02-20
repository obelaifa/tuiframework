#ifndef _XControllerData_h_
#define _XControllerData_h_

#define WIN32_LEAN_AND_MEAN // To prevent redefinition Compiling Errors
#include <windows.h> // Must be included before Xinput.h
#include <tuiframework/core/ISerializable.h>

#include <Xinput.h>
#pragma comment(lib, "XINPUT9_1_0.LIB")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one

/**
 * \brief Encapsulate the Gamepad-Inputs.
 *
 * \author Sebastian Keppler
 * \date 04.02.2016
 *
 * \sa tuiframework::ISerializable
 */

class XControllerData : public tuiframework::ISerializable {
public:

	/** \brief Defines an alias representing the Gamepad-Inputs */
	typedef enum
{
	GamePad_Button_DPAD_UP          = XINPUT_GAMEPAD_DPAD_UP,
	GamePad_Button_DPAD_DOWN        = XINPUT_GAMEPAD_DPAD_DOWN,
	GamePad_Button_DPAD_LEFT        = XINPUT_GAMEPAD_DPAD_LEFT,
	GamePad_Button_DPAD_RIGHT       = XINPUT_GAMEPAD_DPAD_RIGHT,
	GamePad_Button_START            = XINPUT_GAMEPAD_START,
	GamePad_Button_BACK             = XINPUT_GAMEPAD_BACK,
	GamePad_Button_LEFT_THUMB       = XINPUT_GAMEPAD_LEFT_THUMB,
	GamePad_Button_RIGHT_THUMB      = XINPUT_GAMEPAD_RIGHT_THUMB,
	GamePad_Button_LEFT_SHOULDER    = XINPUT_GAMEPAD_LEFT_SHOULDER,
	GamePad_Button_RIGHT_SHOULDER   = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	GamePad_Button_A                = XINPUT_GAMEPAD_A,
	GamePad_Button_B                = XINPUT_GAMEPAD_B,
	GamePad_Button_X                = XINPUT_GAMEPAD_X,
	GamePad_Button_Y                = XINPUT_GAMEPAD_Y,
	GamePadButton_Max =             14
}GamePadButton;

	/**
	 * \brief Default constructor.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 */

	XControllerData();

	/**
	 * \brief Constructor.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param id The identifier.
	 */

	XControllerData(int id);

	/**
	 * \brief Destructor.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 */

	virtual ~XControllerData();

	/**
	 * \brief Gets the identifier.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The identifier.
	 */

	int getId() const;

	/**
	 * \brief Sets an identifier.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param id The identifier.
	 */

	void setId(int id);

	/**
	 * \brief Gets the left Thumbstick x-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The left Thumbstick x-coordinate.
	 */

	int getLThumbDeltaX() const;

	/**
	 * \brief Gets left Thumbstick y-ycoordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The left Thumbstick y-ycoordinate.
	 */

	int getLThumbDeltaY() const;

	/**
	 * \brief Sets left Thumbstick x-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param deltaX The left Thumbstick x-coordinate..
	 */

	void setLThumbDeltaX(int deltaX);

	/**
	 * \brief Sets left Thumbstick y-coordinate..
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param deltaY left Thumbstick y-coordinate..
	 */

	void setLThumbDeltaY(int deltaY);

	/**
	 * \brief Gets right Thumbstick x-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The right Thumbstick x-coordinate.
	 */

	int getRThumbDeltaX() const;

	/**
	 * \brief Gets right Thumbstick y-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The right Thumbstick y-coordinate.
	 */

	int getRThumbDeltaY() const;

	/**
	 * \brief Sets right Thumbstick x-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param deltaX The right Thumbstick x-coordinate.
	 */

	void setRThumbDeltaX(int deltaX);

	/**
	 * \brief Sets right Thumbstick y-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param deltaY The right Thumbstick y-coordinate.
	 */

	void setRThumbDeltaY(int deltaY);

	/**
	 * \brief Gets left shoulder z-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The left shoulder z-coordinate.
	 */

	int getLShoulderDeltaZ() const;

	/**
	 * \brief Gets right shoulder z-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return The right shoulder z-coordinate.
	 */

	int getRShoulderDeltaZ() const;

	/**
	 * \brief Sets left shoulder z-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param deltaZ The left shoulder z-coordinate.
	 */

	void setLShoulderDeltaZ(int deltaZ);

	/**
	 * \brief Sets right shoulder z-coordinate.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param deltaZ The right shoulder z-coordinate.
	 */

	void setRShoulderDeltaZ(int deltaZ);

	/**
	 * \brief Gets butto-state.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param code Button-Code.
	 *
	 * \return true if Button from Button-code is pressed, false if not.
	 */

	bool getButtonStateChange(GamePadButton code) const;

	/**
	 * \brief Sets button code.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param buttonCode The Button-code.
	 */

	void setButtonCode(unsigned int buttonCode);

	/**
	 * \brief Checks if ButtonState or ThumbStick/Shoulder Values has changed.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return true if changed, false if not.
	 */

	bool hasChanged() const;

    /**
     * \brief Serialize Stream for Output.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param [in,out] os The operating system.
     *
     * \return A std::ostream&amp;
     */

    virtual std::ostream & serialize(std::ostream & os) const;

    /**
     * \brief Deserialize Stream for Input.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param [in,out] is The is.
     *
     * \return A std::istream&amp;
     */

    virtual std::istream & deSerialize(std::istream & is);

	/**
	 * \brief Checks if Controller is Connected.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \return true if connected, false if not.
	 */

	bool is_connected();

	/**
	 * \brief activate Vibration on Controller.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 */

	void Vibrate();


protected:
	/** \brief The identifier. */
	int id;
	/** \brief The left Thumbstick x-coordinate. */
	int lThumbdeltaX;
	/** \brief The left Thumbstick y-<coordinate. */
	int lThumbdeltaY;

	/** \brief The right Thumbstick x-coordinate. */
	int rThumbdeltaX;
	/** \brief The right Thumbstick y-coordinate. */
	int rThumbdeltaY;

	/** \brief The left shoulder z-coordinate. */
	int lShoulderdeltaZ;
	/** \brief The right shoulder z-coordinate. */
	int rShoulderdeltaZ;

	/** \brief The button code. */
	unsigned int buttonCode;
private:
	/** \brief State of the controller. */
	XINPUT_STATE _controllerState;
};

#endif