#pragma once

#include <exception>
#include <string>

namespace alce
{
	namespace exception 
	{
		class Exception : public std::exception
		{
		public:

			Exception(std::string title, std::string cause = "")
			{
				message = "\033[31m[Alce::Exception::" + title + "]\033[0m";
				if(cause != "") 
				{
					message += "\n\033[33m" + cause + "\033[0m";
				}
			}

			const char* what() const noexcept override
			{
				return message.c_str();
			}

		protected:

			std::string message;
		};

		class NullPointerException : public Exception
		{
		public:

			NullPointerException(std::string cause) : Exception("NullPointerException", cause)
			{
				
			}
		};

		class ParseException : public Exception
		{
		public:

			ParseException(std::string cause = "") : Exception("ParseException", cause)
			{

			}
		};

		namespace collections
		{

			class CollectionsException : public Exception
			{
			public:

				CollectionsException(std::string title, std::string cause = "") : Exception("Collections::" + title, cause)
				{

				}
			};

			class EmptyListException : public CollectionsException
			{
			public:
				
				EmptyListException(std::string cause = "") : CollectionsException("EmptyListException", cause)
				{

				}
			};

			class OutOfBoundsException : public CollectionsException
			{
			public:

				OutOfBoundsException(std::string cause = "") : CollectionsException("OutOfBoundsException", cause)
				{

				}
			};

			class NotFoundKeyException : public CollectionsException
			{
			public:

				NotFoundKeyException(std::string cause = "") : CollectionsException("NotFoundKeyException", cause)
				{

				}
			};
		}

		namespace filesystem
		{
			class FileSystemException : public Exception
			{
			public:

				FileSystemException(std::string title, std::string cause = "") : Exception("FileSystem::" + title, cause)
				{

				}
			};

			class NullFileException : public FileSystemException
			{
			public:

				NullFileException(std::string cause = "") : FileSystemException("NullFileException", cause)
				{

				}
			};

			class NullFolderException : public FileSystemException
			{
			public: 

				NullFolderException(std::string cause = "") : FileSystemException("NullFolderException", cause)
				{

				}
			};
		
			class InvalidOperationException : public FileSystemException
			{
			public:

				InvalidOperationException(std::string cause = "") : FileSystemException("InvalidOperationException", cause)
				{

				}
			};
		}

		namespace json
		{
			class JsonException : public Exception
			{
			public:

				JsonException(std::string title, std::string cause = "") : Exception("Json::" + title, cause)
				{

				}
			};

			class UnsupportedTypeException : public JsonException
			{
			public:

				UnsupportedTypeException(std::string cause = "") : JsonException("UnsupportedTypeException", cause)
				{

				}
			};

			class NullMemberException : public JsonException
			{
			public:

				NullMemberException(std::string cause = "") : JsonException("NullMemberException", cause)
				{

				}
			};

		}
	
		namespace time
		{
			class TimeException : public Exception
			{
			public:

				TimeException(std::string title, std::string cause = "") : Exception("Time::" + title, cause)
				{

				}
			};

			class InvalidMeasureValue : public TimeException
			{
			public:

				InvalidMeasureValue(std::string cause = "") : TimeException("InvalidMeasureValue", cause)
				{
					
				}
			};
		}

		namespace resources
		{
			class InvalidFont : public Exception
			{
			public:
				
				InvalidFont(std::string title, std::string cause = "") : Exception("Resources::" + title, cause)
				{
					
				}
			};
		}
	}
}
