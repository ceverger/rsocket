// iodevice.hpp - описание абстрактного класса IODevice 

#ifndef IO_DEVICE_HPP
#define IO_DEVICE_HPP

	class IODevice
	{
		/* Класса управляет абстрактным устройством ввода-вывода */
		
		public:
			
			enum 
			{  /* Целочисленные идентификаторы типа устройства
					ввода-вывода ------------------------------- */
						
					UnknowType = 0, // Неизвестный тип устройства
					FileType, 		 // Тип устройства - файл
					SocketType      // Тип устройства - сокет
			};
			
		protected:
		
			int fd; // Файловый дескриптор устройства ввода-вывода
			int typeID; // Идентификатор типа устройства ввода вывода		
			const char *errstr; // Строка ошибки
			
		public:
		
			/* Конcтрукторы и деструкторы класса */
		
				IODevice() : fd(-1), typeID(UnknowType), errstr(nullptr) {}
				virtual ~IODevice() {}
				
			/* Селекторы класса */
			
				int getFD() const { return fd; }
				int getTypeID() const { return typeID; }
				const char *getErrstr() const { return errstr; }
				
			/* Создание устройства ввода-вывода */
			
				virtual bool createIO() { return false; }
				
			/* Виртуальные методы для открытия и закрытия 
			   устройства ввода-вывода ------------------ */
						
				virtual bool openIO()  { return false; } 
				virtual bool closeIO() { return false; }
				
			/* Абстрактные виртуальные для записи и чтения устройства
			   ввода-вывода ----------------------------------------- */
				
				virtual int rddata(char *buf, int size)        { return 0; }
				virtual int wrdata(const char *buf, int size)  { return 0; }
			
	}; // class IODevice

#endif // IO_DEVICE_HPP
