#ifndef _WinModData_h_
#define _WinModData_h_

#define WIN32_LEAN_AND_MEAN // To prevent redefinition Compiling Errors

#include <windows.h> 
#include <tuiframework/core/ISerializable.h>

#include "PackedType.h"

using namespace std;

/**
 * \brief Class for WinMod-data.
 *
 * Encapsulate all data from WinMod in one Object
 * 
 * \author Sebastian Keppler
 * \date 04.02.2016
 *
 * \sa tuiframework::ISerializable
 */

class WinModData : public tuiframework::ISerializable {
public:

	/**
	 * \brief Default constructor.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 */

	WinModData();

	/**
	 * \brief Destructor.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 */

	virtual ~WinModData();

    /**
     * \brief Serialize Stream for Output.
     *
     * \author Sebastian Keppler
     * \date 04.02.2016
     *
     * \param [in,out] os The output-stream.
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
     * \param [in,out] is The input stream.
     *
     * \return A std::istream&amp;
     */

    virtual std::istream & deSerialize(std::istream & is);


	/**
	 * \brief Sets the floats.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param [in,out] floats If non-null, the floats.
	 * \param floatSize		  Size of the floats.
	 */

	void setFloats(float* floats,int floatSize);

	
	/**
	 * \brief Sets Word-Values.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param [in,out] dwords If non-null, the dwords.
	 * \param dwordSize		  Size of the DWord-Values.
	 */

	void setDWords(unsigned long* dwords,int dwordSize);

	/**
	 * \brief Sets the Word-Values.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param [in,out] words If non-null, the words.
	 * \param wordSize		 Size of the word-Values.
	 */

	void setWords(unsigned short* words,int wordSize);

	/**
	 * \brief Sets the byte-Values.
	 *
	 * \author Sebastian Keppler
	 * \date 04.02.2016
	 *
	 * \param [in,out] floats If non-null, the floats.
	 * \param byteSize		  Size of the byte-Values.
	 */

	void setBytes(int* floats,int byteSize);


	PackedType<float> getFloatList() const;
	PackedType<int> getByteList() const;
	PackedType<WORD> getWordList() const;
	PackedType<DWORD> getDWordList() const;

protected: 
	
	PackedType<int> byteValues2;
	PackedType<float> floatValues2;
	PackedType<WORD> wordValues2;
	PackedType<DWORD> dWordValues2;
private:

};

#endif