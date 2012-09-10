<?php
$this->pageTitle=Yii::t('base',Yii::app()->name) . ' - '.Yii::t('base','Change Password');
$this->breadcrumbs=array(
	//Yii::t('base','Change Password'),
	InformationManagementModule::t('user', 'Change Password'),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('user', 'Change Password')); ?></h1>

<p class="note">
	<?php echo InformationManagementModule::t('user','Please fill out the following form with your login credentials:'); ?>
	</p>

<div class="form">
<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'changePassword-form',
	'enableClientValidation'=>true,
	'clientOptions'=>array(
		'validateOnSubmit'=>true,
	),
)); ?>

	<p class="note">
	<?php echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); ?>
	</p>

	<div class="row">
		<?php echo $form->labelEx($model,'password'); ?>
		<?php echo $form->passwordField($model,'password'); ?>
		<?php echo $form->error($model,'password'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'password_new'); ?>
		<?php echo $form->passwordField($model,'password_new_repeat'); ?>
		<?php echo $form->error($model,'password_new'); ?>
	</div>
	
	<div class="row">
		<?php echo $form->labelEx($model,'password_new_repeat'); ?>
		<?php echo $form->passwordField($model,'password_new'); ?>
		<?php echo $form->error($model,'password_new_repeat'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton(InformationManagementModule::t('other','Submit')); ?>
	</div>

<?php $this->endWidget(); ?>
</div><!-- form -->
