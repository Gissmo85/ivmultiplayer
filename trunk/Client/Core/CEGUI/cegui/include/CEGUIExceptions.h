/***********************************************************************
    filename:   CEGUIExceptions.h
    created:    20/2/2004
    author:     Paul D Turner, Frederico Jeronimo (fjeronimo)

    purpose:    Defines exceptions used within the system
*************************************************************************/
/***************************************************************************
*   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
*
*   Permission is hereby granted, free of charge, to any person obtaining
*   a copy of this software and associated documentation files (the
*   "Software"), to deal in the Software without restriction, including
*   without limitation the rights to use, copy, modify, merge, publish,
*   distribute, sublicense, and/or sell copies of the Software, and to
*   permit persons to whom the Software is furnished to do so, subject to
*   the following conditions:
*
*   The above copyright notice and this permission notice shall be
*   included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
*   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
*   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
*   OTHER DEALINGS IN THE SOFTWARE.
***************************************************************************/
#ifndef _CEGUIExceptions_h_
#define _CEGUIExceptions_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include <exception>

#undef _FILE_
#undef _LINE_
#define _FILE_ __FILE__
#define _LINE_ __LINE__
// TODO: Enable this for release
//#define _FILE_ ""
//#define _LINE_ 0

// Start of CEGUI namespace section
namespace CEGUI
{
//! Root exception class used within the GUI system.
class  CEGUIEXPORT Exception : public std::exception
{
public:
    //! Virtual destructor.
    virtual ~Exception(void) throw();

    /*!
    \brief
        Return a reference to the String object describing the reason for the
        exception being thrown.

    \return
        String object containing a message describing the reason for the
        exception.
    */
    const String& getMessage(void) const
        { return d_message; }

    /*!
    \brief
        Return a reference to the String object containing the exception name
        (i.e. class type).

    \return
        String object containing the exception name.
    */
    const String& getName() const
        { return d_name; }

    /*!
    \brief
        Return a reference to the String object containing the name of the file
        where the exception occurred.

    \return
        String object containing the name of the file where the exception
        occurred.
    */
    const String& getFileName(void) const
        { return d_filename; }

    /*!
    \brief
        Return the line number where the exception occurred.

    \Return
        Integer representing the line number where the exception occurred.
    */
    int getLine(void) const
        { return d_line; }

    // override from std::exception.
    const char* what() const throw();

protected:
    /*!
    \brief
        Protected constructor that prevents instantiations (users should employ
        derived exception classes instead) and that is responsible for logging
        the exception.

    \param message
        String object describing the reason for the exception being thrown.

    \param name
        String object describing the exception class name
        (e.g. CEGUI::UnknownObjectException)

    \param filename
        String object containing the name of the file where the exception
        occurred.

    \param line
        Integer representing the line number where the exception occurred.
    */
    Exception(const String& message = "",
              const String& name = "CEGUI::Exception",
              const String& filename = "",
              int line = 0);

    //! Holds the reason for the exception being thrown.
    String d_message;
    //! Holds the name of the file where the exception occurred.
    String d_filename;
    //! Holds the class name of the exception (e.g. CEGUI::ObjectInUseException)
    String d_name;
    //! Holds the line number where the exception occurred.
    int d_line;
    //! Holds the default error message.
    String d_what;
};

//----------------------------------------------------------------------------//

//! Exception class used when none of the other classes are applicable
class CEGUIEXPORT GenericException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the generic exception by
        calling the base class.

    \param message
        String object describing the reason for the generic exception being
        thrown.

    \param filename
        String object containing the name of the file where the generic
        exception occurred.

    \param line
        Integer representing the line number where the generic exception
        occurred.

    \remarks
        The generic exception name is automatically passed to the base class as
        "CEGUI::GenericException".
    */
    GenericException(const String& message,
                     const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::GenericException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    generic exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define GenericException(message)  \
    GenericException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used when a request was made for an unknown object
class CEGUIEXPORT UnknownObjectException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the unknown object exception
        by calling the base class.

    \param message
        String object describing the reason for the unknown object exception
        being thrown.

    \param filename
        String object containing the name of the file where the unknown object
        exception occurred.

    \param line
        Integer representing the line number where the unknown object exception
        occurred.

    \remarks
        The unknown object exception name is automatically passed to the base
        class as "CEGUI::UnknownObjectException".
    */
    UnknownObjectException(const String& message,
                           const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::UnknownObjectException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    unknown object exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define UnknownObjectException(message)  \
    UnknownObjectException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used when some impossible request was made of the system.
class CEGUIEXPORT InvalidRequestException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the invalid request
        exception by calling the base class.

    \param message
        String object describing the reason for the invalid request exception
        being thrown.

    \param filename
        String object containing the name of the file where the invalid request
        exception occurred.

    \param line
        Integer representing the line number where the invalid request exception
        occurred.

    \remarks
        The invalid request exception name is automatically passed to the base
        class as "CEGUI::InvalidRequestException".
    */
    InvalidRequestException(const String& message,
                            const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::InvalidRequestException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    invalid request exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define InvalidRequestException(message)  \
    InvalidRequestException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used when a file handling problem occurs
class CEGUIEXPORT FileIOException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the file IO exception by
        calling the base class.

    \param message
        String object describing the reason for the file IO exception being
        thrown.

    \param filename
        String object containing the name of the file where the file IO
        exception occurred.

    \param line
        Integer representing the line number where the file IO exception
        occurred.

    \remarks
        The file IO exception name is automatically passed to the base class as
        "CEGUI::FileIOException".
    */
    FileIOException(const String& message,
                    const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::FileIOException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    file IO exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define FileIOException(message)  \
    FileIOException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used for problems in the rendering subsystem classes.
class CEGUIEXPORT RendererException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the renderer exception by
        calling the base class.

    \param message
        String object describing the reason for the renderer exception being
        thrown.

    \param filename
        String object containing the name of the file where the renderer
        exception occurred.

    \param line
        Integer representing the line number where the renderer exception
        occurred.

    \remarks
        The renderer exception name is automatically passed to the base class as
        "CEGUI::RendererException".
    */
    RendererException(const String& message,
                      const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::RendererException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    renderer exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define RendererException(message)  \
    RendererException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

/*!
\brief
    Exception class used when an attempt is made create a named object of a
    particular type when an object of the same type already exists with the same
    name.
*/
class CEGUIEXPORT AlreadyExistsException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the already exists exception
        by calling the base class.

    \param message
        String object describing the reason for the already exists exception
        being thrown.

    \param filename
        String object containing the name of the file where the already exists
        exception occurred.

    \param line
        Integer representing the line number where the already exists exception
        occurred.

    \remarks
        The already exists exception name is automatically passed to the base
        class as "CEGUI::AlreadyExistsException".
    */
    AlreadyExistsException(const String& message,
                           const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::AlreadyExistsException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    already exists exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define AlreadyExistsException(message)  \
    AlreadyExistsException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used when a memory handling error is detected
class CEGUIEXPORT MemoryException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the memory exception by
        calling the base class.

    \param message
        String object describing the reason for the memory exception being
        thrown.

    \param filename
        String object containing the name of the file where the memory exception
        occurred.

    \param line
        Integer representing the line number where the memory exception
        occurred.

    \remarks
        The memory exception name is automatically passed to the base class as
        "CEGUI::MemoryException".
    */
    MemoryException(const String& message,
                    const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::MemoryException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    memory exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define MemoryException(message)  \
    MemoryException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used when some required object or parameter is null
class CEGUIEXPORT NullObjectException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the null object exception by
        calling the base class.

    \param message
        String object describing the reason for the null object exception being
        thrown.

    \param filename
        String object containing the name of the file where the null object
        exception occurred.

    \param line
        Integer representing the line number where the null object exception
        occurred.

    \remarks
        The null object exception name is automatically passed to the base class
        as "CEGUI::NullObjectException".
    */
    NullObjectException(const String& message,
                        const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::NullObjectException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    null object exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define NullObjectException(message)  \
    NullObjectException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

/*!
\brief
    Exception class used when some attempt to delete, remove, or otherwise
    invalidate some object that is still in use occurs.
*/
class CEGUIEXPORT ObjectInUseException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the object in use exception
        by calling the base class.

    \param message
        String object describing the reason for the object in use exception
        being thrown.

    \param filename
        String object containing the name of the file where the object in use
        exception occurred.

    \param line
        Integer representing the line number where the object in use exception
        occurred.

    \remarks
        The object in use exception name is automatically passed to the base
        class as "CEGUI::ObjectInUseException".
    */
    ObjectInUseException(const String& message,
                         const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::ObjectInUseException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    object in use exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define ObjectInUseException(message)  \
    ObjectInUseException(message, _FILE_, _LINE_)

//----------------------------------------------------------------------------//

//! Exception class used for issues in scripting subsystem.
class CEGUIEXPORT ScriptException : public Exception
{
public:
    /*!
    \brief
        Constructor that is responsible for logging the script exception by
        calling the base class.

    \param message
        String object describing the reason for the script exception being
        thrown.

    \param filename
        String object containing the name of the file where the script exception
        occurred.

    \param line
        Integer representing the line number where the script exception
        occurred.

    \remarks
        The script exception name is automatically passed to the base class as
        "CEGUI::ScriptException".
    */
    ScriptException(const String& message,
                    const String& file = "unknown", int line = 0) :
        Exception(message, "CEGUI::ScriptException", file, line)
    {}
};

/*!
\brief
    This helper macro ensures the correct filename and line number where the
    script exception occurred are passed to the exception itself.

\remarks
    There's a bug in Visual Studio 7.1
    (see http://support.microsoft.com/kb/199057/en) and lower which leads to
    incorrect _LINE_ macro expansion if used inside a function and compiled
    with "Program Database for Edit & Continue" (/ZI) where instead of a
    constant expressing line number you'll get the following:
    (_LINE_Var+constant).  The workaround consists in using compiler option
    "Program Database" (/Zi) instead --> Project Properties\C/C++\General\Debug
    Information Format\Program Database (/Zi).  Visual Studio 2005 corrects the
    problem. Premake files were modified to contemplate this for VS2002 and
    VS2003.
*/
#define ScriptException(message)  \
    ScriptException(message, _FILE_, _LINE_)


//----------------------------------------------------------------------------//

} // End of  CEGUI namespace section


#endif // end of guard _CEGUIExceptions_h_