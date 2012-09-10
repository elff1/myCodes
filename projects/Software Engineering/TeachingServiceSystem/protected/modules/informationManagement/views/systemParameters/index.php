<?php
//顶部导航栏
$this->breadcrumbs=array(
	'System Parameters',
);?>
<h1><?php echo $this->id . '/' . $this->action->id; ?></h1>

<p>
	You can edit these variables through <?php echo Yii::getPathOfAlias('application.config').DIRECTORY_SEPARATOR.'main.php'.'.' ?></br>
	<br/>
	<br/>
	<?php
	foreach (Yii::app()->params as $name=>$value){
		echo $name.': '.$value.'<br/>';
	}
	?>
</p>
