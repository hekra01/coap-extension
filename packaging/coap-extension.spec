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
Requires: libcoap

%description
Crosswalk Tizen extension for libCoAp.

%package	demo
%define 	_demodir	%{_datadir}/widget_demo
Summary: 	Demo app using CrossXalk coap extension
Group:          Applications/Multimedia
Provides:       coap-extension-demo
Requires:       coap-extension
BuildArch:      noarch
BuildRequires: 	pkgconfig(openssl)
BuildRequires: 	zip
BuildRequires: 	vim-base

%description	demo
%{summary}.

%prep
%setup -q

%build
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot} PREFIX=%{_prefix}

%files
%{_prefix}/lib/tizen-extensions-crosswalk/libcoap-extension.so

%files		demo
%{_demodir}/xwalk-coap-extension-demo.xpk
%{_demodir}/xwalk-coap-extension-demo.wgt
