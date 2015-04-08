CloudCVBackend
==============

A C++ backend module for CloudCV. This library exports selected image processing algorithms to Node.js. 
It does data marshalling and asynchronous processing according to Node.js paradigm.
This variant of CloudCV (see https://github.com/BloodAxe/CloudCV for the original) has object detection implemented. 


## Continuous integration status 
[![Build Status](https://travis-ci.org/BloodAxe/CloudCVBackend.png?branch=master)](https://travis-ci.org/BloodAxe/CloudCVBackend)

Regular builds and testing provided by https://travis-ci.org.


Test Instructions
=================

You can manually test the object detection portion of code by going to:

	$> src/test/manual_test

run the test by invoking node's javascript...

	$> node manualNumbersDetectionTest.js 


This will run the example file that runs a face detection on the 
picture indicated in the test file.


Note
====

The classifier and image file both have to be in the same directory as the test javascript files.