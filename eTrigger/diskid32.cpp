///////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////

#include "stdwx.h"

#ifdef WIN32
#include "diskid32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////
int DiskID::ReadPhysicalDriveInNTWithAdminRights (void)
{
   int done = FALSE;
   int drive = 0;

   for (drive = 0; drive < MAX_IDE_DRIVES; ++drive)
   {
      HANDLE hPhysicalDriveIOCTL = 0;

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      char driveName [256];

      sprintf (driveName, "\\\\.\\PhysicalDrive%d", drive);
	  wxString driveName2 = driveName;

         //  Windows NT, Windows 2000, must have admin rights
      hPhysicalDriveIOCTL = CreateFile (driveName2,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE , NULL,
                               OPEN_EXISTING, 0, NULL);
      // if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      //    printf ("Unable to open physical drive %d, error code: 0x%lX\n",
      //            drive, GetLastError ());

      if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      {
#ifdef PRINTING_TO_CONSOLE_ALLOWED
         if (PRINT_DEBUG) 
			 printf ("\n%d ReadPhysicalDriveInNTWithAdminRights ERROR"
					 "\nCreateFile(%s) returned INVALID_HANDLE_VALUE\n",
		 			 __LINE__, driveName);
#endif
      }
      else
      {
         GETVERSIONOUTPARAMS2 VersionParams;
         DWORD               cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
         memset ((void*) &VersionParams, 0, sizeof(VersionParams));

         if ( ! DeviceIoControl (hPhysicalDriveIOCTL, DFP_GET_VERSION,
                   NULL, 
                   0,
                   &VersionParams,
                   sizeof(VersionParams),
                   &cbBytesReturned, NULL) )
         {         
#ifdef PRINTING_TO_CONSOLE_ALLOWED
            if (PRINT_DEBUG)
            {
	           DWORD err = GetLastError ();
	           printf ("\n%d ReadPhysicalDriveInNTWithAdminRights ERROR"
		               "\nDeviceIoControl(%d, DFP_GET_VERSION) returned 0, error is %d\n",
		               __LINE__, (int) hPhysicalDriveIOCTL, (int) err);
		    }
#endif
         }

            // If there is a IDE device at number "i" issue commands
            // to the device
         if (VersionParams.bIDEDeviceMap <= 0)
         {
#ifdef PRINTING_TO_CONSOLE_ALLOWED
            if (PRINT_DEBUG)
	            printf ("\n%d ReadPhysicalDriveInNTWithAdminRights ERROR"
		                "\nNo device found at position %d (%d)\n",
		                __LINE__, (int) drive, (int) VersionParams.bIDEDeviceMap);
#endif
         }
         else
         {
            BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
            SENDCMDINPARAMS2  scip;
            //SENDCMDOUTPARAMS OutCmd;

			   // Now, get the ID sector for all IDE devices in the system.
               // If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
               // otherwise use the IDE_ATA_IDENTIFY command
            bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? \
                      IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

            memset (&scip, 0, sizeof(scip));
            memset (IdOutCmd, 0, sizeof(IdOutCmd));

            if ( DoIDENTIFY (hPhysicalDriveIOCTL, 
                       &scip, 
                       (PSENDCMDOUTPARAMS2)&IdOutCmd, 
                       (BYTE) bIDCmd,
                       (BYTE) drive,
                       &cbBytesReturned))
            {
               DWORD diskdata [256];
               int ijk = 0;
               USHORT *pIdSector = (USHORT *)
                             ((PSENDCMDOUTPARAMS2) IdOutCmd) -> bBuffer;

               for (ijk = 0; ijk < 256; ++ijk)
                  diskdata [ijk] = pIdSector [ijk];

               PrintIdeInfo (drive, diskdata);

               done = TRUE;
            }
	    }

         CloseHandle (hPhysicalDriveIOCTL);
      }
   }

   return done;
}

//////////////////////////////////////////
int DiskID::ReadPhysicalDriveInNTUsingSmart (void)
{
   int done = FALSE;
   int drive = 0;

   for (drive = 0; drive < MAX_IDE_DRIVES; ++drive)
   {
      HANDLE hPhysicalDriveIOCTL = 0;

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      char driveName [256];

      sprintf (driveName, "\\\\.\\PhysicalDrive%d", drive);

         //  Windows NT, Windows 2000, Windows Server 2003, Vista
	  wxString driveName2 = driveName;
      hPhysicalDriveIOCTL = CreateFile (driveName2,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
							   NULL, OPEN_EXISTING, 0, NULL);
      // if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      //    printf ("Unable to open physical drive %d, error code: 0x%lX\n",
      //            drive, GetLastError ());

      if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      {
#ifdef PRINTING_TO_CONSOLE_ALLOWED
         if (PRINT_DEBUG) 
			 printf ("\n%d ReadPhysicalDriveInNTUsingSmart ERROR"
					 "\nCreateFile(%s) returned INVALID_HANDLE_VALUE\n"
					 "Error Code %d\n",
		 			 __LINE__, driveName, GetLastError ());
#endif
      }
      else
      {
         GETVERSIONINPARAMS2 GetVersionParams;
         DWORD cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
         memset ((void*) & GetVersionParams, 0, sizeof(GetVersionParams));

         if ( ! DeviceIoControl (hPhysicalDriveIOCTL, SMART_GET_VERSION,
                   NULL, 
                   0,
     			   &GetVersionParams, sizeof (GETVERSIONINPARAMS2),
				   &cbBytesReturned, NULL) )
         {         
#ifdef PRINTING_TO_CONSOLE_ALLOWED
            if (PRINT_DEBUG)
            {
	           DWORD err = GetLastError ();
	           printf ("\n%d ReadPhysicalDriveInNTUsingSmart ERROR"
		               "\nDeviceIoControl(%d, SMART_GET_VERSION) returned 0, error is %d\n",
		               __LINE__, (int) hPhysicalDriveIOCTL, (int) err);
		    }
#endif
         }
         else
         {
			 	// Print the SMART version
           	// PrintVersion (& GetVersionParams);
	           // Allocate the command buffer
			ULONG CommandSize = sizeof(SENDCMDINPARAMS2) + IDENTIFY_BUFFER_SIZE;
        	PSENDCMDINPARAMS2 Command = (PSENDCMDINPARAMS2) malloc (CommandSize);
	           // Retrieve the IDENTIFY data
	           // Prepare the command
#define ID_CMD          0xEC            // Returns ID sector for ATA
			Command -> irDriveRegs.bCommandReg = ID_CMD;
			DWORD BytesReturned = 0;
	        if ( ! DeviceIoControl (hPhysicalDriveIOCTL, 
				                    SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS2),
									Command, CommandSize,
									&BytesReturned, NULL) )
            {
		           // Print the error
		        //PrintError ("SMART_RCV_DRIVE_DATA IOCTL", GetLastError());
	        } 
			else
			{
        	       // Print the IDENTIFY data
                DWORD diskdata [256];
                USHORT *pIdSector = (USHORT *)
                             (PIDENTIFY_DATA) ((PSENDCMDOUTPARAMS2) Command) -> bBuffer;

                for (int ijk = 0; ijk < 256; ++ijk)
                   diskdata [ijk] = pIdSector [ijk];

                PrintIdeInfo (drive, diskdata);
                done = TRUE;
			}
	           // Done
            CloseHandle (hPhysicalDriveIOCTL);
			free (Command);
		 }
      }
   }

   return done;
}

	//  function to decode the serial numbers of IDE hard drives
	//  using the IOCTL_STORAGE_QUERY_PROPERTY command 
/////////////////////////////////////////////////////////////////////////////////
char * DiskID::flipAndCodeBytes (const char * str, int pos, int flip, char * buf)
{
   int i;
   int j = 0;
   int k = 0;

   buf [0] = '\0';
   if (pos <= 0)
      return buf;

   if ( ! j)
   {
      char p = 0;

      // First try to gather all characters representing hex digits only.
      j = 1;
      k = 0;
      buf[k] = 0;
      for (i = pos; j && str[i] != '\0'; ++i)
      {
	 char c = tolower(str[i]);

	 if (isspace(c))
	    c = '0';

	 ++p;
	 buf[k] <<= 4;

	 if (c >= '0' && c <= '9')
	    buf[k] |= (unsigned char) (c - '0');
	 else if (c >= 'a' && c <= 'f')
	    buf[k] |= (unsigned char) (c - 'a' + 10);
	 else
	 {
	    j = 0;
	    break;
	 }

	 if (p == 2)
	 {
	    if (buf[k] != '\0' && ! isprint(buf[k]))
	    {
	       j = 0;
	       break;
	    }
	    ++k;
	    p = 0;
	    buf[k] = 0;
	 }

      }
   }

   if ( ! j)
   {
      // There are non-digit characters, gather them as is.
      j = 1;
      k = 0;
      for (i = pos; j && str[i] != '\0'; ++i)
      {
	     char c = str[i];

	     if ( ! isprint(c))
	     {
	        j = 0;
	        break;
	     }

	     buf[k++] = c;
      }
   }

   if ( ! j)
   {
      // The characters are not there or are not printable.
      k = 0;
   }

   buf[k] = '\0';

   if (flip)
      // Flip adjacent characters
      for (j = 0; j < k; j += 2)
      {
	     char t = buf[j];
	     buf[j] = buf[j + 1];
	     buf[j + 1] = t;
      }

   // Trim any beginning and end space
   i = j = -1;
   for (k = 0; buf[k] != '\0'; ++k)
   {
      if (! isspace(buf[k]))
      {
	     if (i < 0)
	        i = k;
	     j = k;
      }
   }

   if ((i >= 0) && (j >= 0))
   {
      for (k = i; (k <= j) && (buf[k] != '\0'); ++k)
         buf[k - i] = buf[k];
      buf[k - i] = '\0';
   }

   return buf;
}

//////////////////////////////////////////////////////
int DiskID::ReadPhysicalDriveInNTWithZeroRights (void)
{
   int done = FALSE;
   int drive = 0;

   for (drive = 0; drive < MAX_IDE_DRIVES; ++drive)
   {
      HANDLE hPhysicalDriveIOCTL = 0;

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      char driveName [256];

      sprintf (driveName, "\\\\.\\PhysicalDrive%d", drive);

         //  Windows NT, Windows 2000, Windows XP - admin rights not required
	  wxString driveName2 = driveName;
      hPhysicalDriveIOCTL = CreateFile (driveName2, 0,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);
      if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      {
#ifdef PRINTING_TO_CONSOLE_ALLOWED
         if (PRINT_DEBUG)
             printf ("\n%d ReadPhysicalDriveInNTWithZeroRights ERROR"
		             "\nCreateFile(%s) returned INVALID_HANDLE_VALUE\n",
		             __LINE__, driveName);
#endif
      }
      else
      {
		 STORAGE_PROPERTY_QUERY query;
         DWORD cbBytesReturned = 0;
		 char buffer [10000];

         memset ((void *) & query, 0, sizeof (query));
		 query.PropertyId = StorageDeviceProperty;
		 query.QueryType = PropertyStandardQuery;

		 memset (buffer, 0, sizeof (buffer));

         if ( DeviceIoControl (hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,
                   & query,
                   sizeof (query),
				   & buffer,
				   sizeof (buffer),
                   & cbBytesReturned, NULL) )
         {         
			 STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *) & buffer;
			 char serialNumber [1000];
			 char modelNumber [1000];
             char vendorId [1000];
	         char productRevision [1000];

#ifdef PRINTING_TO_CONSOLE_ALLOWED
             if (PRINT_DEBUG)
             {
                 printf ("\n%d STORAGE_DEVICE_DESCRIPTOR contents for drive %d\n"
		                 "                Version: %ld\n"
		                 "                   Size: %ld\n"
		                 "             DeviceType: %02x\n"
		                 "     DeviceTypeModifier: %02x\n"
		                 "         RemovableMedia: %d\n"
		                 "        CommandQueueing: %d\n"
		                 "         VendorIdOffset: %4ld (0x%02lx)\n"
		                 "        ProductIdOffset: %4ld (0x%02lx)\n"
		                 "  ProductRevisionOffset: %4ld (0x%02lx)\n"
		                 "     SerialNumberOffset: %4ld (0x%02lx)\n"
		                 "                BusType: %d\n"
		                 "    RawPropertiesLength: %ld\n",
		                 __LINE__, drive,
			             (unsigned long) descrip->Version,
		                 (unsigned long) descrip->Size,
		                 (int) descrip->DeviceType,
		                 (int) descrip->DeviceTypeModifier,
		                 (int) descrip->RemovableMedia,
		                 (int) descrip->CommandQueueing,
		                 (unsigned long) descrip->VendorIdOffset,
		                 (unsigned long) descrip->VendorIdOffset,
		                 (unsigned long) descrip->ProductIdOffset,
		                 (unsigned long) descrip->ProductIdOffset,
		                 (unsigned long) descrip->ProductRevisionOffset,
		                 (unsigned long) descrip->ProductRevisionOffset,
		                 (unsigned long) descrip->SerialNumberOffset,
		                 (unsigned long) descrip->SerialNumberOffset,
		                 (int) descrip->BusType,
		                 (unsigned long) descrip->RawPropertiesLength);

	            dump_buffer ("Contents of RawDeviceProperties",
			                 (unsigned char*) descrip->RawDeviceProperties,
			                 descrip->RawPropertiesLength);

	            dump_buffer ("Contents of first 256 bytes in buffer",
			                 (unsigned char*) buffer, 256);
			 }
#endif
             flipAndCodeBytes (buffer,
                               descrip -> VendorIdOffset,
			                   0, vendorId );
	         flipAndCodeBytes (buffer,
			                   descrip -> ProductIdOffset,
			                   0, modelNumber );
	         flipAndCodeBytes (buffer,
			                   descrip -> ProductRevisionOffset,
			                   0, productRevision );
	         flipAndCodeBytes (buffer,
			                   descrip -> SerialNumberOffset,
			                   1, serialNumber );

			 if (0 == HardDriveSerialNumber [0] &&
						//  serial number must be alphanumeric
			            //  (but there can be leading spaces on IBM drives)
				   (isalnum (serialNumber [0]) || isalnum (serialNumber [19])))
			 {
				strcpy (HardDriveSerialNumber, serialNumber);
				strcpy (HardDriveModelNumber, modelNumber);
				done = TRUE;
			 }
#ifdef PRINTING_TO_CONSOLE_ALLOWED
             printf ("\n**** STORAGE_DEVICE_DESCRIPTOR for drive %d ****\n"
		             "Vendor Id = [%s]\n"
		             "Product Id = [%s]\n"
		             "Product Revision = [%s]\n"
		             "Serial Number = [%s]\n",
		             drive,
		             vendorId,
		             modelNumber,
		             productRevision,
		             serialNumber);
#endif
	           // Get the disk drive geometry.
	         memset (buffer, 0, sizeof(buffer));
	         if ( ! DeviceIoControl (hPhysicalDriveIOCTL,
			          IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,
			          NULL,
			          0,
			          &buffer,
			          sizeof(buffer),
			          &cbBytesReturned,
			          NULL))
	         {
#ifdef PRINTING_TO_CONSOLE_ALLOWED
                if (PRINT_DEBUG)
	               printf ("\n%d ReadPhysicalDriveInNTWithZeroRights ERROR"
		                   "|nDeviceIoControl(%s, IOCTL_DISK_GET_DRIVE_GEOMETRY_EX) returned 0",
		                   driveName);
#endif
          	 }
	         else
	         {         
	            DISK_GEOMETRY_EX2* geom = (DISK_GEOMETRY_EX2*) &buffer;
	            int fixed = (geom->Geometry.MediaType == FixedMedia);
	            __int64 size = geom->DiskSize.QuadPart;
				     
#ifdef PRINTING_TO_CONSOLE_ALLOWED
	            printf ("\n**** DISK_GEOMETRY_EX for drive %d ****\n"
		                "Disk is%s fixed\n"
		                "DiskSize = %I64d\n",
		                drive,
		                fixed ? "" : " NOT",
		                size);
#endif
	        }
         }
		 else
		 {
			 DWORD err = GetLastError ();
#ifdef PRINTING_TO_CONSOLE_ALLOWED
			 printf ("\nDeviceIOControl IOCTL_STORAGE_QUERY_PROPERTY error = %d\n", err);
#endif
		 }

         CloseHandle (hPhysicalDriveIOCTL);
      }
   }

   return done;
}

   // DoIDENTIFY
   // FUNCTION: Send an IDENTIFY command to the drive
   // bDriveNum = 0-3
   // bIDCmd = IDE_ATA_IDENTIFY or IDE_ATAPI_IDENTIFY
////////////////////////////////////////////////////////////////////////////
BOOL DiskID::DoIDENTIFY (HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS2 pSCIP,
                 PSENDCMDOUTPARAMS2 pSCOP, BYTE bIDCmd, BYTE bDriveNum,
                 PDWORD lpcbBytesReturned)
{
      // Set up data structures for IDENTIFY command.
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
   pSCIP -> irDriveRegs.bFeaturesReg = 0;
   pSCIP -> irDriveRegs.bSectorCountReg = 1;
   //pSCIP -> irDriveRegs.bSectorNumberReg = 1;
   pSCIP -> irDriveRegs.bCylLowReg = 0;
   pSCIP -> irDriveRegs.bCylHighReg = 0;

      // Compute the drive number.
   pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

      // The command can either be IDE identify or ATAPI identify.
   pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
   pSCIP -> bDriveNumber = bDriveNum;
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;

   return ( DeviceIoControl (hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
               (LPVOID) pSCIP,
               sizeof(SENDCMDINPARAMS2) - 1,
               (LPVOID) pSCOP,
               sizeof(SENDCMDOUTPARAMS2) + IDENTIFY_BUFFER_SIZE - 1,
               lpcbBytesReturned, NULL) );
}


////////////////////////////////////////
int DiskID::ReadDrivePortsInWin9X (void)
{
   int done = FALSE;
   unsigned long int i = 0;

   HANDLE VxDHandle = 0;
   pt_IdeDInfo pOutBufVxD = 0;
   DWORD lpBytesReturned = 0;

		//  set the thread priority high so that we get exclusive access to the disk
   BOOL status =
		// SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
		SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
		// SetPriorityClass (GetCurrentProcess (), HIGH_PRIORITY_CLASS);

#ifdef PRINTING_TO_CONSOLE_ALLOWED

   if (0 == status) 
	   // printf ("\nERROR: Could not SetThreadPriority, LastError: %d\n", GetLastError ());
	   printf ("\nERROR: Could not SetPriorityClass, LastError: %d\n", GetLastError ());

#endif

      // 1. Make an output buffer for the VxD
   rt_IdeDInfo info;
   pOutBufVxD = &info;

      // *****************
      // KLUDGE WARNING!!!
      // HAVE to zero out the buffer space for the IDE information!
      // If this is NOT done then garbage could be in the memory
      // locations indicating if a disk exists or not.
   ZeroMemory (&info, sizeof(info));

      // 1. Try to load the VxD
       //  must use the short file name path to open a VXD file
   //char StartupDirectory [2048];
   //char shortFileNamePath [2048];
   //char *p = NULL;
   //char vxd [2048];
      //  get the directory that the exe was started from
   //GetModuleFileName (hInst, (LPSTR) StartupDirectory, sizeof (StartupDirectory));
      //  cut the exe name from string
   //p = &(StartupDirectory [strlen (StartupDirectory) - 1]);
   //while (p >= StartupDirectory && *p && '\\' != *p) p--;
   //*p = '\0';   
   //GetShortPathName (StartupDirectory, shortFileNamePath, 2048);
   //sprintf (vxd, "\\\\.\\%s\\IDE21201.VXD", shortFileNamePath);
   //VxDHandle = CreateFile (vxd, 0, 0, 0,
   //               0, FILE_FLAG_DELETE_ON_CLOSE, 0);   
   VxDHandle = CreateFile (L"\\\\.\\IDE21201.VXD", 0, 0, 0,
							0, FILE_FLAG_DELETE_ON_CLOSE, 0);

   if (VxDHandle != INVALID_HANDLE_VALUE)
   {
         // 2. Run VxD function
      DeviceIoControl (VxDHandle, m_cVxDFunctionIdesDInfo,
					0, 0, pOutBufVxD, sizeof(pt_IdeDInfo), &lpBytesReturned, 0);

         // 3. Unload VxD
      CloseHandle (VxDHandle);
   }
   else
		MessageBox (NULL, L"ERROR: Could not open IDE21201.VXD file", 
					L"DiskId32", MB_ICONSTOP);

      // 4. Translate and store data
   for (i=0; i<8; ++i)
   {
      if((pOutBufVxD->DiskExists[i]) && (pOutBufVxD->IDEExists[i/2]))
      {
			DWORD diskinfo [256];
			for (int j = 0; j < 256; ++j) 
				diskinfo [j] = pOutBufVxD -> DisksRawInfo [i * 256 + j];

            // process the information for this buffer
		   PrintIdeInfo (i, diskinfo);
			done = TRUE;
      }
   }

		//  reset the thread priority back to normal
   // SetThreadPriority (GetCurrentThread(), THREAD_PRIORITY_NORMAL);
   SetPriorityClass (GetCurrentProcess (), NORMAL_PRIORITY_CLASS);

   return done;
}


//////////////////////////////////////////////
int DiskID::ReadIdeDriveAsScsiDriveInNT (void)
{
   int done = FALSE;
   int controller = 0;

   for (controller = 0; controller < 16; ++controller)
   {
      HANDLE hScsiDriveIOCTL = 0;
      char   driveName [256];

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      sprintf (driveName, "\\\\.\\Scsi%d:", controller);

         //  Windows NT, Windows 2000, any rights should do
	  wxString driveName2 = driveName;
      hScsiDriveIOCTL = CreateFile (driveName2,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);
      // if (hScsiDriveIOCTL == INVALID_HANDLE_VALUE)
      //    printf ("Unable to open SCSI controller %d, error code: 0x%lX\n",
      //            controller, GetLastError ());

      if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
      {
         int drive = 0;

         for (drive = 0; drive < 2; ++drive)
         {
            char buffer [sizeof (SRB_IO_CONTROL) + SENDIDLENGTH];
            SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
            SENDCMDINPARAMS2 *pin =
                   (SENDCMDINPARAMS2 *) (buffer + sizeof (SRB_IO_CONTROL));
            DWORD dummy;
   
            memset (buffer, 0, sizeof (buffer));
            p -> HeaderLength = sizeof (SRB_IO_CONTROL);
            p -> Timeout = 10000;
            p -> Length = SENDIDLENGTH;
            p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
            strncpy ((char *) p -> Signature, "SCSIDISK", 8);
  
            pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
            pin -> bDriveNumber = drive;

            if (DeviceIoControl (hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) +
                                         sizeof (SENDCMDINPARAMS2) - 1,
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) + SENDIDLENGTH,
                                 &dummy, NULL))
            {
               SENDCMDOUTPARAMS2 *pOut =
                    (SENDCMDOUTPARAMS2 *) (buffer + sizeof (SRB_IO_CONTROL));
               IDSECTOR *pId = (IDSECTOR *) (pOut -> bBuffer);
               if (pId -> sModelNumber [0])
               {
                  DWORD diskdata [256];
                  int ijk = 0;
                  USHORT *pIdSector = (USHORT *) pId;
          
                  for (ijk = 0; ijk < 256; ++ijk)
                     diskdata [ijk] = pIdSector [ijk];

                  PrintIdeInfo (controller * 2 + drive, diskdata);

                  done = TRUE;
               }
            }
         }
         CloseHandle (hScsiDriveIOCTL);
      }
   }

   return done;
}


///////////////////////////////////////////////////////////
void DiskID::PrintIdeInfo (int drive, DWORD diskdata [256])
{
   char serialNumber [1024];
   char modelNumber [1024];
   char revisionNumber [1024];
   char bufferSize [32];

   __int64 sectors = 0;
   __int64 bytes = 0;

      //  copy the hard drive serial number to the buffer
   ConvertToString (diskdata, 10, 19, serialNumber);
   ConvertToString (diskdata, 27, 46, modelNumber);
   ConvertToString (diskdata, 23, 26, revisionNumber);
   sprintf (bufferSize, "%u", diskdata [21] * 512);

   if (0 == HardDriveSerialNumber [0] &&
       //  serial number must be alphanumeric
       //  (but there can be leading spaces on IBM drives)
       (isalnum (serialNumber [0]) || isalnum (serialNumber [19])))
   {
      strcpy (HardDriveSerialNumber, serialNumber);
      strcpy (HardDriveModelNumber, modelNumber);
   }

#ifdef PRINTING_TO_CONSOLE_ALLOWED

   printf ("\nDrive %d - ", drive);

   switch (drive / 2)
   {
      case 0: printf ("Primary Controller - ");
              break;
      case 1: printf ("Secondary Controller - ");
              break;
      case 2: printf ("Tertiary Controller - ");
              break;
      case 3: printf ("Quaternary Controller - ");
              break;
   }

   switch (drive % 2)
   {
      case 0: printf (" - Master drive\n\n");
              break;
      case 1: printf (" - Slave drive\n\n");
              break;
   }

   printf ("Drive Model Number________________: [%s]\n",
           modelNumber);
   printf ("Drive Serial Number_______________: [%s]\n",
           serialNumber);
   printf ("Drive Controller Revision Number__: [%s]\n",
           revisionNumber);

   printf ("Controller Buffer Size on Drive___: %s bytes\n",
           bufferSize);

   printf ("Drive Type________________________: ");
   if (diskdata [0] & 0x0080)
      printf ("Removable\n");
   else if (diskdata [0] & 0x0040)
      printf ("Fixed\n");
   else printf ("Unknown\n");
           
		//  calculate size based on 28 bit or 48 bit addressing
		//  48 bit addressing is reflected by bit 10 of word 83
	if (diskdata [83] & 0x400) 
		sectors = diskdata [103] * 65536I64 * 65536I64 * 65536I64 + 
					diskdata [102] * 65536I64 * 65536I64 + 
					diskdata [101] * 65536I64 + 
					diskdata [100];
	else
		sectors = diskdata [61] * 65536 + diskdata [60];
		//  there are 512 bytes in a sector
	bytes = sectors * 512;
	printf ("Drive Size________________________: %I64d bytes\n",
			bytes);

#endif  // PRINTING_TO_CONSOLE_ALLOWED

   char string1 [1000];
   sprintf (string1, "Drive%dModelNumber", drive);
   WriteConstantString (string1, modelNumber);

   sprintf (string1, "Drive%dSerialNumber", drive);
   WriteConstantString (string1, serialNumber);

   sprintf (string1, "Drive%dControllerRevisionNumber", drive);
   WriteConstantString (string1, revisionNumber);

   sprintf (string1, "Drive%dControllerBufferSize", drive);
   WriteConstantString (string1, bufferSize);

   sprintf (string1, "Drive%dType", drive);
   if (diskdata [0] & 0x0080)
      WriteConstantString (string1, "Removable");
   else if (diskdata [0] & 0x0040)
      WriteConstantString (string1, "Fixed");
   else
      WriteConstantString (string1, "Unknown");
}


///////////////////////////////////////////////////////////////////////////////////////////////
char * DiskID::ConvertToString (DWORD diskdata [256], int firstIndex, int lastIndex, char* buf)
{
   int index = 0;
   int position = 0;

      //  each integer has two characters stored in it backwards
   for (index = firstIndex; index <= lastIndex; ++index)
   {
         //  get high byte for 1st character
      buf [position++] = (char) (diskdata [index] / 256);

         //  get low byte for 2nd character
      buf [position++] = (char) (diskdata [index] % 256);
   }

      //  end the string 
   buf[position] = '\0';

      //  cut off the trailing blanks
   for (index = position - 1; index > 0 && isspace(buf [index]); index--)
      buf [index] = '\0';

   return buf;
}


//////////////////////////////////////
long DiskID::getHardDriveComputerID ()
{
   int done = FALSE;
   // char string [1024];
   __int64 id = 0;
   OSVERSIONINFO version;

   strcpy (HardDriveSerialNumber, "");

   memset (&version, 0, sizeof (version));
   version.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
   GetVersionEx (&version);
   if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		  //  this works under WinNT4 or Win2K if you have admin rights
#ifdef PRINTING_TO_CONSOLE_ALLOWED
		printf ("\nTrying to read the drive IDs using physical access with admin rights\n");
#endif
		done = ReadPhysicalDriveInNTWithAdminRights ();
		

			//  this should work in WinNT or Win2K if previous did not work
			//  this is kind of a backdoor via the SCSI mini port driver into
			//     the IDE drives
#ifdef PRINTING_TO_CONSOLE_ALLOWED
		printf ("\nTrying to read the drive IDs using the SCSI back door\n");
#endif
		// if ( ! done) 
			done = ReadIdeDriveAsScsiDriveInNT ();

		  //  this works under WinNT4 or Win2K or WinXP if you have any rights
#ifdef PRINTING_TO_CONSOLE_ALLOWED
		printf ("\nTrying to read the drive IDs using physical access with zero rights\n");
#endif
		//if ( ! done)
			done = ReadPhysicalDriveInNTWithZeroRights ();

		  //  this works under WinNT4 or Win2K or WinXP or Windows Server 2003 or Vista if you have any rights
#ifdef PRINTING_TO_CONSOLE_ALLOWED
		printf ("\nTrying to read the drive IDs using Smart\n");
#endif
		//if ( ! done)
			done = ReadPhysicalDriveInNTUsingSmart ();

   }
   else
   {
         //  this works under Win9X and calls a VXD
      int attempt = 0;

         //  try this up to 10 times to get a hard drive serial number
      for (attempt = 0;
           attempt < 10 && ! done && 0 == HardDriveSerialNumber [0];
           ++attempt)
         done = ReadDrivePortsInWin9X ();
   }

   if (HardDriveSerialNumber [0] > 0)
   {
      char *p = HardDriveSerialNumber;

      WriteConstantString ("HardDriveSerialNumber", HardDriveSerialNumber);

         //  ignore first 5 characters from western digital hard drives if
         //  the first four characters are WD-W
      if ( ! strncmp (HardDriveSerialNumber, "WD-W", 4)) 
         p += 5;
      for ( ; p && *p; p++)
      {
         if ('-' == *p) 
            continue;
         id *= 10;
         switch (*p)
         {
            case '0': id += 0; break;
            case '1': id += 1; break;
            case '2': id += 2; break;
            case '3': id += 3; break;
            case '4': id += 4; break;
            case '5': id += 5; break;
            case '6': id += 6; break;
            case '7': id += 7; break;
            case '8': id += 8; break;
            case '9': id += 9; break;
            case 'a': case 'A': id += 10; break;
            case 'b': case 'B': id += 11; break;
            case 'c': case 'C': id += 12; break;
            case 'd': case 'D': id += 13; break;
            case 'e': case 'E': id += 14; break;
            case 'f': case 'F': id += 15; break;
            case 'g': case 'G': id += 16; break;
            case 'h': case 'H': id += 17; break;
            case 'i': case 'I': id += 18; break;
            case 'j': case 'J': id += 19; break;
            case 'k': case 'K': id += 20; break;
            case 'l': case 'L': id += 21; break;
            case 'm': case 'M': id += 22; break;
            case 'n': case 'N': id += 23; break;
            case 'o': case 'O': id += 24; break;
            case 'p': case 'P': id += 25; break;
            case 'q': case 'Q': id += 26; break;
            case 'r': case 'R': id += 27; break;
            case 's': case 'S': id += 28; break;
            case 't': case 'T': id += 29; break;
            case 'u': case 'U': id += 30; break;
            case 'v': case 'V': id += 31; break;
            case 'w': case 'W': id += 32; break;
            case 'x': case 'X': id += 33; break;
            case 'y': case 'Y': id += 34; break;
            case 'z': case 'Z': id += 35; break;
         }                            
      }
   }

   id %= 100000000;
   if (strstr (HardDriveModelNumber, "IBM-"))
      id += 300000000;
   else if (strstr (HardDriveModelNumber, "MAXTOR") ||
            strstr (HardDriveModelNumber, "Maxtor"))
      id += 400000000;
   else if (strstr (HardDriveModelNumber, "WDC "))
      id += 500000000;
   else
      id += 600000000;

#ifdef PRINTING_TO_CONSOLE_ALLOWED

   printf ("\nHard Drive Serial Number__________: %s\n", 
           HardDriveSerialNumber);
   printf ("\nHard Drive Model Number___________: %s\n", 
           HardDriveModelNumber);
   printf ("\nComputer ID_______________________: %I64d\n", id);

#endif

   return (long) id;
}

/////////////////////////////////////////////////////////////////////////////////
void DiskID::dump_buffer (const char* title, const unsigned char* buffer, int len)
{
   int i = 0;
   int j;

   printf ("\n-- %s --\n", title);
   if (len > 0)
   {
      printf ("%8.8s ", " ");
      for (j = 0; j < 16; ++j)
      {
	    printf (" %2X", j);
      }
      printf ("  ");
      for (j = 0; j < 16; ++j)
      {
	    printf ("%1X", j);
      }
      printf ("\n");
   }
   while (i < len)
   {
      printf("%08x ", i);
      for (j = 0; j < 16; ++j)
      {
	 if ((i + j) < len)
	    printf (" %02x", (int) buffer[i +j]);
	 else
	    printf ("   ");
      }
      printf ("  ");
      for (j = 0; j < 16; ++j)
      {
	 if ((i + j) < len)
	    printf ("%c", isprint (buffer[i + j]) ? buffer [i + j] : '.');
	 else
	    printf (" ");
      }
      printf ("\n");
      i += 16;
   }
   printf ("-- DONE --\n");
}

char* DiskID::getHardDriveSerial()
{
	getHardDriveComputerID();
	return HardDriveSerialNumber;
}











// Prints the MAC address stored in a 6 byte array to stdout
/////////////////////////////////////////////////////////
void MacAdapter::PrintMACaddress(unsigned char MACData[])
{

#ifdef PRINTING_TO_CONSOLE_ALLOWED

	printf("\nMAC Address: %02X-%02X-%02X-%02X-%02X-%02X\n", 
		MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);

#endif

   char string [256];
   sprintf (string, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], 
			   MACData[2], MACData[3], MACData[4], MACData[5]);
   WriteConstantString ("MACaddress", string);
}



// Fetches the MAC address and prints it
DWORD MacAdapter::GetMACaddress(void)
{
  DWORD MACaddress = 0;
  IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information
                                         // for up to 16 NICs
  DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

  DWORD dwStatus = GetAdaptersInfo(      // Call GetAdapterInfo
			AdapterInfo,                 // [out] buffer to receive data
			&dwBufLen);                  // [in] size of receive data buffer
  assert(dwStatus == ERROR_SUCCESS);  // Verify return value is
                                      // valid, no buffer overflow

  PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to
                                               // current adapter info
  do {
	if (MACaddress == 0)
		MACaddress = pAdapterInfo->Address [5] + pAdapterInfo->Address [4] * 256 + 
					pAdapterInfo->Address [3] * 256 * 256 + 
					pAdapterInfo->Address [2] * 256 * 256 * 256;
    PrintMACaddress(pAdapterInfo->Address); // Print MAC address
    pAdapterInfo = pAdapterInfo->Next;    // Progress through linked list
  }
  while(pAdapterInfo);                    // Terminate if last adapter
  
  return MACaddress;
}

#endif //WIN32












