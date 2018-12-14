PyJadx
======

PyJadx provides Python binding for `Jadx decompiler <https://github.com/skylot/jadx>`_.

As Jadx is written in Java, it use the JNI interface throught `jni.hpp <https://github.com/mapbox/jni.hpp>`_ to make the bridge Java / C++ then it uses `pybind11 <https://github.com/pybind/pybind11>`_
to create the bridge C++ / Python.

.. raw:: html
   
   <p align="center" >   
   <img width="50%" src="https://github.com/romainthomas/pyjadx/blob/master/.github/archi.png"/><br />
   </p>


Getting Start
-------------

.. code-block:: console

  $ git clone https://github.com/romainthomas/pyjadx.git
  $ cd pyjadx
  $ python ./setup.py install --user

You can also build the documentation with:

.. code-block::

  $ python ./setup.py build_sphinx

The generated doc will be located in ``doc/_build/html``

Example
-------

.. code-block:: python

   import pyjadx

   jadx = pyjadx.Jadx()
   app = jadx.load("my.apk")

   for cls in app.classes:
     print(cls.code)

See API reference `here <http://pyjadx.romainthomas.fr/>`_

Credits
-------

This application uses Open Source components. You can find the source code of their open source projects along with license information below.
We acknowledge and are grateful to these developers for their contributions to open source.

:Jadx:
       https://github.com/skylot/jadx

       Copyright 2018 by Skylot

       Licensed under the Apache 2.0 License


:pybind11:
         https://github.com/pybind/pybind11

         `Wenzel Jakob <http://rgl.epfl.ch/people/wjakob>`_

         License (BSD) https://github.com/pybind/pybind11/blob/master/LICENSE

:jni.hpp:
          https://github.com/mapbox/jni.hpp

          `mapbox <https://www.mapbox.com/>`_

          License: https://github.com/mapbox/jni.hpp/blob/master/LICENSE.txt

Authors
-------

Romain Thomas `@rh0main <https://twitter.com/rh0main>`_ - `Quarkslab <https://www.quarkslab.com>`_

