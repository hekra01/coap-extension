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

%package -n 	coap-extension-demo
Summary: 	Demo app using CrossXalk coap extension
Group:          Applications/Multimedia
Provides:       coap-extension-demo
Requires:       coap-extension
BuildArch:      noarch

%description -n coap-extension-demo
%{summary}.

%prep
%setup -q

%build
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot} PREFIX=%{_prefix}
mkdir -p %{buildroot}/usr/share/demos/coap-extension-demo/
cp -rf test/* %{buildroot}/usr/share/demos/coap-extension-demo/
cp -rf *.xpk %{buildroot}/usr/share/demos/coap-extension-demo/


%files
%{_prefix}/lib/tizen-extensions-crosswalk/libcoap-extension.so

%files -n coap-extension-demo
/usr/share/demos/coap-extension-demo/
