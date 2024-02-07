**Unix and Mac: Building the P4PHP Extension**

    To build P4PHP, you need the header files and libraries used by
    PHP and the "phpize" command-line utility. Both of these
    requirements can be met by installing PHP from source or by
    installing the development php packages (php-devel) appropriate
    for your operating system.

    After you have obtained the required files and the phpize utility,
    perform the following steps:

    1. Download the Perforce P4PHP files.
       https://ftp.perforce.com/perforce/r23.1/bin.tools/p4php.tgz
       for the 2023.1 P4PHP.

    2. Download the Perforce C++ API from the Perforce FTP site at
       "https://ftp.perforce.com/perforce". The API archive is located
       in release and platform-specific subdirectories, choose one
       matching OpenSSL version available at target system and the
       C library, for example p4api-glibc2.12-openssl1.1.1.tgz.

       Note: 32-bit builds of P4PHP require a 32-bit version of the
             C++ API and a 32-bit version of PHP. 64-bit builds of
             P4PHP require a 64-bit version of the C++ API and a
             64-bit version of PHP.

    3. Extract both archives into an empty directory.

    4. To build P4PHP, change to the p4php-<version> directory, and run
       the following commands:

           phpize

           ./configure --with-perforce=<path to Perforce C++ API>

           make

    5. To test your P4PHP build, run the following command:

           make test

       Note: the test harness requires a copy of the Perforce server
             executable, p4d, be installed in the current working
             directory.

    6. To install P4PHP, run the following command:

           make install

       Note: the installation typically needs to be performed as
             the root user.

    7. To enable P4PHP, edit your "php.ini" file and add the following
       line:

           extension=perforce.so;

       Note: to locate your "php.ini" file, run the following command:

             php --ini

       Now run:

             php -m

       to confirm that the P4PHP module is being loaded.

    8. To verify that P4PHP works, run the following command:

           php --ri perforce

       If the extension is correctly installed, P4PHP displays
       its version information.

    SSL support
    -----------

    Perforce Server 2023.1 supports SSL connections and the C++ API has
    been compiled with this support. This means that in order to build
    P4PHP, the underlying PHP framework must include OpenSSL.
    

**Windows: Building the P4PHP DLL**

    For instructions how to build P4PHP on windows please contact support@perforce.com
