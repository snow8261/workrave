// WorkraveApplet.cc
//
// Copyright (C) 2002, 2003, 2005, 2006 Rob Caelers & Raymond Penners
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

static const char rcsid[] = "$Id$";

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "debug.hh"

#include "RemoteControl.hh"

#include "GUI.hh"
#include "AppletControl.hh"
#include "GnomeAppletWindow.hh"

#include "Menus.hh"

WR_INIT()

RemoteControl   *RemoteControl::instance = NULL;
WorkraveControl *RemoteControl::workrave_control = NULL;

#include "nls.h"

/************************************************************************/
/* GNOME::RemoteControl                                                 */
/************************************************************************/

RemoteControl::RemoteControl()
{
}


RemoteControl::~RemoteControl()
{
  // FIXME: this causes sme vague error.
  // g_object_unref(workrave_control);
  workrave_control = NULL;
  instance = NULL;
}


RemoteControl *
RemoteControl::get_instance()
{
  if (instance == NULL)
    {
      WorkraveControl *control= workrave_control_new();

      if (control != NULL)
        {
          instance = new RemoteControl();
          
          instance->workrave_control = control;
          instance->workrave_control->_this = instance;
        }
    }
  
  return instance;
}


WR_METHOD_ARGS0_IMPL(void, fire)
{
  AppletControl *applet_control; 
  GnomeAppletWindow *applet_window;
  GUI *gui;

  gui = GUI::get_instance();
  applet_control = gui->get_applet_control();
  applet_window = (GnomeAppletWindow *) applet_control->get_applet_window(AppletControl::APPLET_GNOME);
  
  if (applet_window != NULL)
    {
      applet_window->fire_gnome_applet();
    }
}


WR_METHOD_ARGS0_IMPL(void, open_main)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_open_main_window();
    }
}


WR_METHOD_ARGS0_IMPL(void, open_preferences)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_preferences();
    }
}


WR_METHOD_ARGS0_IMPL(void, open_exercises)
{
#ifdef HAVE_EXERCISES
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_exercises();
    }
#endif
}


WR_METHOD_ARGS0_IMPL(void, open_statistics)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_statistics();
    }
}


WR_METHOD_ARGS0_IMPL(void, open_network_connect)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_network_join();
    }
}


WR_METHOD_ARGS1_IMPL(void, open_network_log, CORBA_boolean, state)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_network_log(state);
    }
}

  
WR_METHOD_ARGS0_IMPL(void, restbreak)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_restbreak_now();
    }
}


WR_METHOD_ARGS1_IMPL(void, set_mode, GNOME_Workrave_WorkraveControl_Mode, mode)
{
  Menus *menus = Menus::get_instance();
  TRACE_ENTER_MSG("RemoteControl::set_mode", mode);
  if (menus != NULL)
    {
      switch (mode)
        {
        case GNOME_Workrave_WorkraveControl_MODE_NORMAL:
          menus->on_menu_normal();
          break;
        case GNOME_Workrave_WorkraveControl_MODE_SUSPENDED:
          menus->on_menu_suspend();
          break;
        case GNOME_Workrave_WorkraveControl_MODE_QUIET:
          menus->on_menu_quiet();
          break;
        default:
          break;
        }
    }
  TRACE_EXIT();
}


WR_METHOD_ARGS0_IMPL(void, disconnect_all)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_network_leave();
    }
}


WR_METHOD_ARGS0_IMPL(void, reconnect_all)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_network_reconnect();
    }
}


WR_METHOD_ARGS0_IMPL(void, quit)
{
  Menus *menus = Menus::get_instance();
  if (menus != NULL)
    {
      menus->on_menu_quit();
    }
}


WR_METHOD_ARGS1_IMPL(void, set_applet_vertical, CORBA_boolean, vertical)
{
  AppletControl *applet_control; 
  GnomeAppletWindow *applet_window;
  GUI *gui;

  gui = GUI::get_instance();
  applet_control = gui->get_applet_control();
  applet_window = (GnomeAppletWindow *) applet_control->get_applet_window(AppletControl::APPLET_GNOME);

  if (applet_window != NULL)
    {
      applet_window->set_applet_vertical(vertical);
    }
}


WR_METHOD_ARGS3_IMPL(void, set_applet_background,
                     CORBA_long, type,
                     const GNOME_Workrave_WorkraveControl_Color *, color,
                     CORBA_long, xid)
{
  AppletControl *applet_control; 
  GnomeAppletWindow *applet_window;
  GUI *gui;

  gui = GUI::get_instance();
  applet_control = gui->get_applet_control();
  applet_window = (GnomeAppletWindow *) applet_control->get_applet_window(AppletControl::APPLET_GNOME);
  
  if (applet_window != NULL)
    {
      GdkColor gdk_color;
      
      if (color != NULL)
        {
          gdk_color.pixel = color->pixel;
          gdk_color.red = color->red;
          gdk_color.green = color->green;
          gdk_color.blue = color->blue;
        }
        
      applet_window->set_applet_background(type, gdk_color, xid);
    }
}

WR_METHOD_ARGS1_IMPL(void, set_applet_size, CORBA_long, size)
{
  AppletControl *applet_control; 
  GnomeAppletWindow *applet_window;
  GUI *gui;

  gui = GUI::get_instance();
  applet_control = gui->get_applet_control();
  applet_window = (GnomeAppletWindow *) applet_control->get_applet_window(AppletControl::APPLET_GNOME);
  
  if (applet_window != NULL)
    {
      applet_window->set_applet_size(size);
    }
}


WR_METHOD_ARGS1_IMPL(void, set_applet, Bonobo_Unknown, bonobo_applet_control)
{
  TRACE_ENTER("set_applet");
  AppletControl *applet_control; 
  GnomeAppletWindow *applet_window;
  GUI *gui;

  gui = GUI::get_instance();
  applet_control = gui->get_applet_control();
  applet_window = (GnomeAppletWindow *) applet_control->get_applet_window(AppletControl::APPLET_GNOME);
  
  if (applet_window != NULL)
    {
      GNOME_Workrave_AppletControl c =
        Bonobo_Unknown_queryInterface(bonobo_applet_control,
                                      "IDL:GNOME/Workrave/AppletControl:1.0",
                                      NULL);
      
      if (c != CORBA_OBJECT_NIL)
        {
          applet_window->set_applet_control(c);
        }
      TRACE_MSG(c);
    }
  TRACE_EXIT();
}


WR_METHOD_ARGS1_IMPL(void, button_clicked, CORBA_long, button)
{
  TRACE_ENTER_MSG("button_clicked", button);
  AppletControl *applet_control; 
  GnomeAppletWindow *applet_window;
  GUI *gui;

  gui = GUI::get_instance();
  applet_control = gui->get_applet_control();
  applet_window = (GnomeAppletWindow *) applet_control->get_applet_window(AppletControl::APPLET_GNOME);
  
  if (applet_window != NULL)
    {
      applet_window->button_clicked(button);
    }
  TRACE_EXIT();
}


/************************************************************************/
/* GNOME::WorkraveControl                                               */
/************************************************************************/

BONOBO_TYPE_FUNC_FULL(WorkraveControl,
                      GNOME_Workrave_WorkraveControl,
                      BONOBO_OBJECT_TYPE,
                      workrave_control);


static void
workrave_control_class_init(WorkraveControlClass *klass)
{
  POA_GNOME_Workrave_WorkraveControl__epv *epv = &klass->epv;

  WR_METHOD_REGISTER(fire);

  WR_METHOD_REGISTER(open_main);
  WR_METHOD_REGISTER(open_preferences);
  WR_METHOD_REGISTER(open_exercises);
  WR_METHOD_REGISTER(open_statistics);
  WR_METHOD_REGISTER(open_network_connect);
  WR_METHOD_REGISTER(open_network_log);
  
  WR_METHOD_REGISTER(restbreak);
  WR_METHOD_REGISTER(set_mode);
  WR_METHOD_REGISTER(disconnect_all);
  WR_METHOD_REGISTER(reconnect_all);
  WR_METHOD_REGISTER(quit);

  WR_METHOD_REGISTER(set_applet_vertical);
  WR_METHOD_REGISTER(set_applet_size);
  WR_METHOD_REGISTER(set_applet);
  WR_METHOD_REGISTER(set_applet_background);
  WR_METHOD_REGISTER(button_clicked);
}


static void
workrave_control_init(WorkraveControl *control)
{
  (void) control;
}


WorkraveControl*
workrave_control_new(void)
{
  Bonobo_RegistrationResult result;

  WorkraveControl *control = (WorkraveControl *)g_object_new(workrave_control_get_type(), NULL);
  BonoboObject *object = BONOBO_OBJECT(control);
    
  result = bonobo_activation_active_server_register("OAFIID:GNOME_Workrave_WorkraveControl",
                                                    bonobo_object_corba_objref(BONOBO_OBJECT(object)));

  if (result == Bonobo_ACTIVATION_REG_ALREADY_ACTIVE)
    {
      control = NULL;
    }
  
  return control;
}


extern "C" BonoboObject*
workrave_component_factory(BonoboGenericFactory *factory, const char *object_id, void *data)
{
  (void) factory;
  (void) data;
  
  BonoboObject *object = NULL;
	  
  g_return_val_if_fail(object_id != NULL, NULL);

  if (!strcmp(object_id, "OAFIID:GNOME_Workrave_WorkraveControl"))
    {
      RemoteControl *control = RemoteControl::get_instance();
      object = BONOBO_OBJECT(control->workrave_control);
    }
  else
    {
      g_warning("Unknown OAFIID '%s'", object_id);
    }


  return object;
}
