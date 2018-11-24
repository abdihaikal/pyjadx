PyJadx
======

PyJadx provides Python binding for `Jadx decompiler <https://github.com/skylot/jadx>`_

Getting Start
-------------

.. code-block:: console

  $ git clone https://github.com/romainthomas/pyjadx.git
  $ cd pyjadx
  $ python ./setup.py install --user

You can also build the documentation using:

.. code-block::

  $ python ./setup.py build_sphinx

The generated doc is located under ``doc/_build/html``

Example
-------

.. code-block:: python

   import pyjadx

   jadx = pyjadx.Jadx()
   jadx.load("my.apk")

   for cls in classes:
     code = cls.code)
     print(code)

Credits
-------

This application uses Open Source components. You can find the source code of their open source projects along with license information below.
We acknowledge and are grateful to these developers for their contributions to open source.

Project: Jadx - https://github.com/skylot/jadx
Copyright 2018 by Skylot
Licensed under the Apache 2.0 License


Project: pybind11 - https://github.com/pybind/pybind11
`Wenzel Jakob <http://rgl.epfl.ch/people/wjakob>`_
License (BSD) https://github.com/pybind/pybind11/blob/master/LICENSE

Project: jni.hpp - https://github.com/mapbox/jni.hpp
`mapbox <https://www.mapbox.com/>`_
License: https://github.com/mapbox/jni.hpp/blob/master/LICENSE.txt

Authors
-------

Romain Thomas `@rh0main <https://twitter.com/rh0main>`_ - `Quarkslab <https://www.quarkslab.com>`_

