<?php
$this->pageTitle=Yii::t('base',Yii::app()->name) . ' - '.Yii::t('base','Error');
$this->breadcrumbs=array(
	Yii::t('base','Error'),
);
?>

<h2><?php echo CHtml::encode(Yii::t('base','Error'));?> <?php echo $code; ?></h2>

<div class="error">
<?php echo CHtml::encode($message); ?>
</div>