Tutorial
========

Once pyjadx installed, one can load Android application as follow:

.. code-block:: python

   import pyjadx

   jadx = pyjadx.Jadx()
   decompiler = jadx.load("com.example.apk")

The ``decompiler`` is an object of type :class:`pyjadx.JadxDecompiler`. Access to the Java code of a single class
can be done as follow:

.. code-block:: python

   clazz = decompiler.get_class("com.example.MyClass")
   print(clazz.code)





