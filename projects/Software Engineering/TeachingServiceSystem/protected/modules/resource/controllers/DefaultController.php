<?php

class DefaultController extends Controller
{
    public $layout='//layouts/column2';
	public function actionIndex()
	{
		$this->render('index');
	}
}
