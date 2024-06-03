# html static pages notes
(Ben Grimer 21/05/22)

## Introduction
This folder contains a number of static html tools written 
at various times.

## The Tools

### anserv_json_gen.html
Used to manipulate anserv manifests - large json structures containing the
details of anserv projects/jobs. Written following some manual editing of
an initial test case for JIRA ticket ECR-4990.

### comma_columns.html
This page generates prettyfied column output similar to the output 
produced by the psql terminal application.

### ConflueceGen.html
This program generates code suitable to be cut/pasted into confluence wiki
using comma/tab delimited output from Navicat.

### comma_in_clause.html
This page will convert a list of inputs to a SQL fragment 
suitable for use with an SQL in clause. It assumes that the 
entries are strings.

### image_linker.html
This is something I put together quickly for Dad.
It allows one to use an image file saved to a google drive
account as a link in Suscipe Domine.

You need to get a link from GDrive (make sure to give access
to All.

Paste the link in the input box and hit 'Transform' then
copy the result.

### onetimepad.html
Simple html/javascript implementation of a onetimepad encryption.

### tracelog_trans.html
This program takes an MCORE tracelog in the keyword substituted format and then
adds back the the keywords (based on the list provided by RichardE on 05/07/19)
