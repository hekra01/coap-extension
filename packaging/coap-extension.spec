Name:     coap-extension
Version:  0.1
Release:  1
Summary:  Example Crosswalk Tizen extension
Group:    System/Libraries

License:    BSD-3-Clause
URL:      https://crosswalk-project.org/
Source0:  %{name}-%{version}.tar.gz

BuildRequires: python
Requires: crosswalk

%description
Example Crosswalk Tizen extension.

%prep
%setup -q

%build
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot} PREFIX=%{_prefix}

%files
%{_prefix}/lib/tizen-extensions-crosswalk/libcoap-extension.so


