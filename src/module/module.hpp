#ifndef HDRIVER
#define HDRIVER

class Module
{
public:
	enum loadResult
	{
		LDSUCCESS = 0, // Success
		LDINITSWFAILURE, // Software failure during initialization.
		LDINITHWFAILURE, // Hardware failure during initialization, if the module is a hardware driver.
		LDNOMATCHINGHW, // Module initialization failed because the module did not detect the hardware it's targeting.
	};

	// Load a kernel module / driver.
	virtual loadResult moduleLoad() = 0;

	// Close a module
	void moduleExit();

	// Return the module name
	const char* getModuleName() const { return name; }

private:
	const char* name = "Unknown module";
};

#endif
