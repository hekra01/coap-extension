Name:     coap-extension
Version:  0.1
Release:  1
Summary:  Crosswalk Tizen extension for libCoAP
Group:    System/Libraries

License:  Apache v2.0 
URL:      https://github.com/cisco-open-source/coap-extension
Source0:  %{name}-%{version}.tar.gz

BuildRequires: python
Requires: crosswalk

%description
Crosswalk Tizen extension for libCoAp.

%prep
%setup -q

%build
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot} PREFIX=%{_prefix}

%files
%{_prefix}/lib/tizen-extensions-crosswalk/libcoap-extension.so


